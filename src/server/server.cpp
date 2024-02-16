#include "server.h"
#include <server/core/game.h>
#include <shared/helper_macros.h>
#include <core/variant/variant.h>
#include <core/string/ustring.h>

ObjectPtr<Game> Server::game;

ObjectPtr<Game> Server::get_game()
{
    return game;
}

void Server::_ready()
{
    DISABLE_IN_EDITOR();
    int server_port = 7654;

    Error err = server_peer->create_server(7654, 32);
    scene_multiplayer = Object::cast_to<SceneMultiplayer>(get_multiplayer().ptr());

    ERR_FAIL_COND(!scene_multiplayer);
    scene_multiplayer->set_root_path(get_path());    
    scene_multiplayer->set_multiplayer_peer(server_peer);

    server_peer->connect("peer_connected", callable_mp(this, &Server::on_peer_connect));
    server_peer->connect("peer_disconnected", callable_mp(this, &Server::on_peer_disconnect));

    if(err == Error::OK)
    {
        print_line("Server is listening on port", server_port);
    }
    else
    {
        print_line("Failed to create server! Error code: " + err);
    }
}

//Peer_id might conflict with ObjectID's
void Server::on_peer_connect(int peer_id) {
	print_line(peer_id, "connected");
	Ref<PackedScene> ent_scene = ResourceLoader::load("res://resources/entities/Entity.tscn");
	Entity *ent_instance = Object::cast_to<Entity>(ent_scene->instantiate());
	ent_instance->set_name(itos(peer_id));
	get_node(NodePath("/root/Server/Game/Level/Entities"))->add_child(ent_instance);
}

void Server::on_peer_disconnect(int peer_id) {
	print_line(peer_id, "disconnected");
	Entity *ent = static_cast<Entity *>(get_node_or_null(NodePath("/root/Server/Game/Level/Entities/" + itos(peer_id))));
    ERR_FAIL_NULL("No such entity!");
    ent->queue_free();
}

void Server::_init() {
    //Setup networking
    server_peer.instantiate(); //Same as using memnew

    game = memnew(Game);
    game->set_name("Game");
    add_child(game.get_ptr());
}

Server::Server()
{

}