#include "server.h"
#include <server/core/game.h>
#include <shared/helper_macros.h>
#include <core/variant/variant.h>
#include <core/string/ustring.h>

#include <scene/main/timer.h>
#include <shared/entities/mercenaries/mercenary.hpp>

void Server::_ready()
{
    DISABLE_IN_EDITOR();
    int server_port = 7654;

    Error err = server_peer->create_server(7654, 32);
    scene_multiplayer = Object::cast_to<SceneMultiplayer>(get_multiplayer().ptr());

    ERR_FAIL_COND(!scene_multiplayer);
    scene_multiplayer->set_root_path(get_path());
    scene_multiplayer->set_multiplayer_peer(server_peer);

    server_peer->connect("peer_connected", callable_mp(this, &Server::_on_peer_connect));
    server_peer->connect("peer_disconnected", callable_mp(this, &Server::_on_peer_disconnect));

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

//Peer_id might conflict with ObjectID's
/*
void Server::on_peer_connect(int peer_id) {
	print_line(peer_id, "connected");
	Ref<PackedScene> ent_scene = ResourceLoader::load("res://resources/entities/Entity.tscn");
	Entity *ent_instance = Object::cast_to<Entity>(ent_scene->instantiate());
	ent_instance->set_name(itos(peer_id));
	get_node(NodePath("/root/Server/Game/Level/Entities"))->add_child(ent_instance);
}
*/

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
    print_line("Peer", peer_id, "connected! Awaiting playerdata...");
    //Connected peer MUST send playerdata within 5 seconds or be kicked
    Timer *timer = memnew(Timer);
    timer->set_autostart(true);
    timer->set_wait_time(5);
    timer->set_one_shot(true);
    timer->set_name("playerdata_timeout" + itos(peer_id));

    Callable callable = callable_mp(game, &Game::_on_playerdata_fail);
    //TODO: See if it works
    timer->connect("timeout", callable.bind(peer_id));

    add_child(timer);
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
    //Setup networking
    server_peer.instantiate(); //Same as using memnew

    game = memnew(Game);
    game->set_name("Game");
    add_child(game);

    set_process(true);
}

void Server::server_rpc_disconnect(const String reason) {

}

void Server::client_rpc_playerdata(Dictionary playerdata) {
	int peer_id = get_multiplayer()->get_remote_sender_id();

    if (!connected_players.has(peer_id)) {
        Variant nickname = playerdata.get_valid("nickname");
        Variant mercenary = playerdata.get_valid("mercenary");

        // TODO: Introduce validator class to avoid long 'if' statements
        if (
            nickname.get_type() == Variant::STRING 
            && mercenary.get_type() == Variant::STRING ) {
            // All good
            Player *ply = memnew(Player);
            ply->change_nickname(String(nickname));
            ply->set_choosen_mercenary(String(mercenary));

            Ref<PackedScene> merc_scene = ResourceLoader::load("res://resources/entities/Mercenary.tscn");

            Mercenary *ent = static_cast<Mercenary *>(merc_scene->instantiate());
            ent->set_name(itos(ent->get_instance_id()));
            ply->set_controlled_entity(ent);
            game->get_current_level()->add_entity(ent);

            //Don't timeout player - we got what we wanted
            Timer *timer = static_cast<Timer *>(get_node_or_null("playerdata_timeout" + itos(peer_id)));
            if (timer) {
                timer->stop();
                timer->queue_free();
            }

            connected_players.insert(peer_id, ply);

            // Send gameinfo
            // NOTE: Currently friend, maybe use getter/setter later?
            rpc_id(peer_id, "server_rpc_gameinfo", game->gameinfo);
        } else {
            // Something wrong - disconnect that peer
            disconnect_peer(peer_id, "Invalid playerdata!");
        }
    } else {
        disconnect_peer(peer_id, "Peer is already connected!");
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

void Server::server_rpc_gameinfo(Dictionary p_gameinfo) {

}

void Server::_bind_methods() {
    ClassDB::bind_method(D_METHOD("server_rpc_disconnect"), &Server::server_rpc_disconnect);
    ClassDB::bind_method(D_METHOD("client_rpc_playerdata"), &Server::client_rpc_playerdata);
    ClassDB::bind_method(D_METHOD("server_rpc_gameinfo", "gameinfo"), &Server::server_rpc_gameinfo);

}

Server::Server()
{

}