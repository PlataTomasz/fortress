#include "server.h"
#include <server/core/game.h>
#include <shared/helper_macros.h>
#include <core/variant/variant.h>
#include <core/string/ustring.h>

#include <scene/main/timer.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <core/io/marshalls.h>

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

void Server::_on_peer_connect(int peer_id)
{
    
    Ref<PackedScene> scene = ResourceLoader::load("res://entities/mercenaries/Barbarian.tscn");
    Mercenary *mercenary = static_cast<Mercenary *>(scene->instantiate());

	mercenary->set_name("p_" + itos(peer_id));
	game->get_current_level()->add_entity(mercenary);
    connected_players.get(peer_id)->set_controlled_entity(mercenary);
    rpc_id(peer_id, "server_rpc_set_controlled_entity", mercenary->get_name());
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
    DISABLE_IN_EDITOR();
    //Setup networking
    server_peer.instantiate(); //Same as using memnew

    game = memnew(Game);
    game->set_name("Game");
    add_child(game);

    set_process(true);

    players = memnew(Node);
    players->set_name("Players");
    add_child(players);
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
    ERR_FAIL_COND_V_MSG(!(String(var_mercenary_name).length() > 3 && String(var_mercenary_name).length() <= 16), ERR_INVALID_DATA, "Nickname of " + itos(peer_id) + " failed validation!");

    Player *ply = memnew(Player);
    ply->change_nickname(var_nickname.operator String());
    ply->set_choosen_mercenary(var_mercenary_name.operator String());

    Ref<PackedScene> scene = ResourceLoader::load("res://entities/mercenaries/Barbarian.tscn");
    Mercenary *mercenary = static_cast<Mercenary *>(scene->instantiate());
    mercenary->set_name(itos(get_instance_id()));
    
    ply->set_controlled_entity(mercenary);

    add_player(peer_id, ply);
    print_line("Auth succeeded on server for peer ", peer_id);
    scene_multiplayer->complete_auth(peer_id);
    print_line("Player", ply->get_nickname(), "joined the game!");
    return OK;
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

void Server::add_player(int peer_id, Ref<Player> player) { 
    if(!connected_players.has(peer_id)) {
        connected_players.insert(peer_id, player);
    }
    //Peer already exists - don't add
};

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
}

Server::Server()
{

}