#include "server.h"
#include <server/core/game.h>
#include <shared/helper_macros.h>

ObjectPtr<Game> Server::get_game()
{
    return game;
}

void Server::_ready()
{
    //Setup game object
    game = memnew(Game);
    add_child(game.get_ptr());

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

Server::Server()
{
    DISABLE_IN_EDITOR();
    //Required, so that Node can tick
    set_process(true);

    //Setup networking
    server_peer.instantiate(); //Same as using memnew
}