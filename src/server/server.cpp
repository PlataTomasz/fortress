#include "server.h"
#include <server/core/game.h>
#include <shared/helper_macros.h>
#include <core/variant/variant.h>
#include <core/string/ustring.h>

#include <scene/main/timer.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <core/io/marshalls.h>

#include <shared/registries/mercenary_registry.h>

#include <core/variant/variant_utility.h>
#include <shared/gamemodes/gamemode.h>
#include <server/core/console_cmd/disconnect_peer_console_command.h>
#include <scene/main/scene_tree.h>

Server *Server::instance = nullptr;

void Server::_ready()
{
    DISABLE_IN_EDITOR();
    int server_port = 7654;

    Error err = server_peer->create_server(7654, 32);
    scene_multiplayer = Object::cast_to<SceneMultiplayer>(get_multiplayer().ptr());
    scene_multiplayer->set_auth_callback(callable_mp(this, &Server::auth_callback));
    scene_multiplayer->connect("peer_authenticating", callable_mp(this, &Server::_on_auth_start));
    scene_multiplayer->connect("peer_authentication_failed", callable_mp(this, &Server::_on_auth_fail));

    ERR_FAIL_COND(!scene_multiplayer);
    scene_multiplayer->set_root_path(get_path());
    scene_multiplayer->set_multiplayer_peer(server_peer);

    scene_multiplayer->connect("peer_connected", callable_mp(this, &Server::_on_peer_connect));
    scene_multiplayer->connect("peer_disconnected", callable_mp(this, &Server::_on_peer_disconnect));

    if(err == Error::OK)
    {
        print_line("Server is listening on port", server_port);
    }
    else
    {
        print_line("Failed to create server! Error code: " + err);
    }
}

void Server::process() {

}

void Server::disconnect_peer(int peer_id, const String reason) {
    rpc_id(peer_id, "server_rpc_disconnect", reason);
    //Workaround, so rpc containing disconnect reason have chance to arrive to client, but... Real disconnect will occur in 1s and with high latency that time still might not be enough
    Callable disconnect_callable = callable_mp(scene_multiplayer, &SceneMultiplayer::disconnect_peer);
    Ref<SceneTreeTimer> timer = SceneTree::get_singleton()->create_timer(1.0f);
    timer->connect("timeout", disconnect_callable.bind(peer_id));
}

void Server::_on_peer_disconnect(int peer_id)
{
    Timer *timer = static_cast<Timer *>(get_node_or_null("playerdata_timeout" + itos(peer_id)));
    if (timer) {
        timer->stop();
        timer->queue_free();
    }
}

Server *Server::get_instance() {
    return instance;
}

void Server::_on_peer_connect(int peer_id)
{
    Mercenary *mercenary = nullptr;
    if(connected_players.has(peer_id)) {
        Ref<Player> ply = connected_players.get(peer_id);

        if(!ply->get_controlled_entity()) {
            String mercenary_name = ply->get_choosen_mercenary();
            mercenary = MercenaryRegistry::get_singleton()->create_instance(mercenary_name);

            ERR_FAIL_NULL(mercenary);
            mercenary->set_meta("spawned_for_player", ply);
            mercenary->set_name("p_" + itos(peer_id));
            mercenary->set_meta("spawned_by_player_connect", true);
            game->get_current_level()->add_entity(mercenary);
            
            connected_players.get(peer_id)->set_controlled_entity(mercenary);
        } else {
            mercenary = ply->get_controlled_entity();
        }

        rpc_id(peer_id, "server_rpc_set_controlled_entity", mercenary->get_name());
        emit_signal("player_connected", ply);
    }
}

/*
void Server::on_peer_disconnect(int peer_id) {
	print_line(peer_id, "disconnected");
	Entity *ent = static_cast<Entity *>(get_node_or_null(NodePath("/root/Server/Game/Level/Entities/" + itos(peer_id))));
    ERR_FAIL_NULL("No such entity!");
    ent->queue_free();
}
*/

void Server::_init() {
    instance = this;

    DISABLE_IN_EDITOR();
    //Setup networking
    server_peer.instantiate(); //Same as using memnew

    // TODO: Dependency injection instead
    game = memnew(Game);
    game->set_name("Game");
    add_child(game);

    set_process(true);

    players = memnew(Node);
    players->set_name("Players");
    add_child(players);

    _setup_console_commands();

    command_listening_thread.instantiate();
    command_listening_thread->start(callable_mp(this, &Server::_await_console_command), core_bind::Thread::PRIORITY_NORMAL);
}

void Server::change_player_peer_id(const Ref<Player>& player_to_alter, int new_peer_id) {
    for(KeyValue<int, Ref<Player>> kv : connected_players) {
        Ref<Player> player = kv.value;
        ERR_CONTINUE(player.is_null());

        if(player == player_to_alter) {
            connected_players.replace_key(kv.key, new_peer_id);
            player->set_owner_peer_id(new_peer_id);
            break;
        }
    }
}

void Server::_await_console_command() {
    while(true) {
        String console_input = core_bind::OS::get_singleton()->read_string_from_stdin();
        PackedStringArray console_input_words = console_input.split(" ");

        if(console_input_words.size() != 0) {
            String console_command_name = console_input_words[0];
            PackedStringArray command_arguments = console_input_words.size() > 1 ? (console_input_words.slice(1, console_input_words.size())) : PackedStringArray();

            callable_mp(this, &Server::execute_server_command).call_deferred(console_command_name, command_arguments);
        }
    }
}

void Server::_setup_console_commands() {
    add_console_command("disconnect_peer", memnew(DisconnectPeerConsoleCommand(this)));
}

void Server::add_console_command(const String& command_name, ServerConsoleCommand *command_object) {
    ERR_FAIL_COND_MSG(defined_console_commands.has(command_name), "Command with such name is already registered!");
    defined_console_commands.insert(command_name, command_object);
}

Error Server::execute_server_command(const String& command_name, PackedStringArray command_arguments) {
    ERR_FAIL_COND_V_MSG(!defined_console_commands.has(command_name), Error::ERR_INVALID_PARAMETER, "Command with such name doesn't exist!");
    // TODO: Move into separate class/method/template/idk yet
    Array command_arguments_array;
    for(const String& command_argument : command_arguments) {
        command_arguments_array.push_back(VariantUtilityFunctions::str_to_var(command_argument));
    }

    return defined_console_commands.get(command_name)->execute(command_arguments_array);
}

void Server::server_rpc_disconnect(const String reason) {
    
}

Error Server::auth_callback(int peer_id, PackedByteArray data) {
    Variant var;
    Error data_err = decode_variant(var, data.ptr(), data.size());
    ERR_FAIL_COND_V_MSG(data_err != OK, data_err, "Received invalid auth data from" + itos(peer_id));
    ERR_FAIL_COND_V_MSG(var.get_type() != Variant::DICTIONARY, ERR_INVALID_DATA, "Received invalid auth data from" + itos(peer_id));

    Dictionary playerdata = var.operator Dictionary();
    Variant var_nickname = playerdata.get_valid("nickname");
    ERR_FAIL_COND_V_MSG(var_nickname.get_type() != Variant::STRING, ERR_INVALID_DATA, "Nickname is malformed!" + itos(peer_id));

    Variant var_mercenary_name = playerdata.get_valid("mercenary");
    ERR_FAIL_COND_V_MSG(var_mercenary_name.get_type() != Variant::STRING, ERR_INVALID_DATA, "Mercenary name is malformed!" + itos(peer_id));
    
    //TODO: Proper nickname and choosen mercenary name validation - Currently hardcoded here
    //ERR_FAIL_COND_V_MSG(!(String(var_mercenary_name).length() > 3 && String(var_mercenary_name).length() <= 16), ERR_INVALID_DATA, "Nickname of " + itos(peer_id) + " failed validation!");

    print_line("Peer", itos(peer_id), "wants to play character named", var_mercenary_name);

    // If there is already player with such nickname and it is not connected, then take control of that player
    // If player with such nickname exists, but is connected by other player, then kick peer that attempted to take controll
    // If player with such nickname doesn't exist, create it

    Ref<Player> player_with_matching_nickname = find_player_by_nickname(String(var_nickname));
    Ref<Player> player_to_add;
    if(!player_with_matching_nickname.is_null()) {
        if(is_player_currently_connected(player_with_matching_nickname)) {
            // Kick impostor
            return Error::ERR_ALREADY_IN_USE;
        } else {
            player_to_add = player_with_matching_nickname;
            change_player_peer_id(player_to_add, peer_id);
        }
    } else {
        // TODO: Wrap such variant to type conversions in a dedicated class! They are causing me a headache!
        String mercenary_name_str = String(var_mercenary_name);
        ERR_FAIL_COND_V_MSG(!(MercenaryRegistry::get_singleton()->has(mercenary_name_str)), Error::ERR_INVALID_PARAMETER, "Invalid mercenary name received from client! Auth failed for " + peer_id);

        player_to_add.instantiate();
        player_to_add->change_nickname(String(var_nickname));
        player_to_add->set_choosen_mercenary(mercenary_name_str);
        player_to_add->set_owner_peer_id(peer_id);
        add_player(peer_id, player_to_add);
    }

    
    print_line("Auth succeeded on server for peer ", peer_id);
    scene_multiplayer->complete_auth(peer_id);
    print_line("Player", player_to_add->get_nickname(), "joined the game!");
    return OK;
}

bool Server::is_player_currently_connected(const Ref<Player>& player) {
    ERR_FAIL_NULL_V(scene_multiplayer, false);

    for(KeyValue<int, Ref<Player>> kv : connected_players) {
        Ref<Player> player = kv.value;
        ERR_CONTINUE(player.is_null());

        for(int peer_id : scene_multiplayer->get_peer_ids()) {
            if(peer_id == kv.key) {
                return true;
            }
        }
    }

    return false;
}

void Server::_on_auth_start(int peer_id) {
    int len = 0;
    Error err = encode_variant(game->gameinfo, nullptr, len, false, 0);
    ERR_FAIL_COND(err);

    PackedByteArray buffer;
    buffer.resize(len);

    encode_variant(game->gameinfo, buffer.ptrw(), len, false, 0);

    scene_multiplayer->send_auth(peer_id, buffer);
}

void Server::_on_auth_fail(int peer_id) {
    print_error("Authentication failed for " + itos(peer_id));
    remove_player(peer_id);
}

void Server::remove_player(int peer_id) {
    if(connected_players.has(peer_id)) {
        connected_players.erase(peer_id);
    }
}

Ref<Player> Server::find_player_by_nickname(const String& nickname) {
    for(KeyValue<int, Ref<Player>> var : connected_players) {
        Ref<Player> player = var.value;
        ERR_CONTINUE(player.is_null());

        if(player->get_nickname() == nickname) {
            return player;
        }
    }
    
    return Ref<Player>();
}

void Server::add_player(int peer_id, Ref<Player> player) { 
    if(!connected_players.has(peer_id)) {
        connected_players.insert(peer_id, player);
        emit_signal("new_player_join", player);
    }
    //Peer already exists - don't add
};

bool Server::is_peer_connected(int peer_id) {
    Vector<int> connected_peer_ids = scene_multiplayer->get_peer_ids();
    
    return connected_peer_ids.has(peer_id);
}

Ref<Player> Server::get_player(int peer_id) {
	if (connected_players.has(peer_id)) {
		return connected_players.get(peer_id);
	}
	return Ref<Player>();
}

void Server::server_rpc_set_controlled_entity(String entity_name) {

}

void Server::_bind_methods() {
    ClassDB::bind_method(D_METHOD("server_rpc_disconnect"), &Server::server_rpc_disconnect);
    ClassDB::bind_method(D_METHOD("server_rpc_set_controlled_entity", "entity_name"), &Server::server_rpc_set_controlled_entity);

    ADD_SIGNAL(MethodInfo("new_player_join", PropertyInfo(Variant::OBJECT, "player")));
    ADD_SIGNAL(MethodInfo("player_connected", PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_RESOURCE_TYPE, Player::get_class_static())));
}

Server::Server()
{

}