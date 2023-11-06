#include "server.h"
#include <server/core/s_game.h>
#include <server/networking/requests/request_handler.h>
#include <server/core/s_game.h>

void Server::on_receive(Ref<ENetPacketPeer> sender, const uint8_t *packet_data, uint64_t size)
{
    //S_GameCommand *game_command = SGameCommandFactory::create(packet_data, size);
    
    

    //ERR_FAIL_COND_MSG(!game_command, "Received message couldn't be converted to GameCommand!");
    
    //game->put_game_command(game_command);

//    RequestHandler::handle_request(sender, packet_data, size);
}

S_Game *Server::get_game()
{
    return game;
}

void Server::ready()
{
        game = memnew(S_Game);
        game->set_name("Game");
        add_child(game);

        int server_port = 7654;

        //Setup networking
        server_peer.instantiate(); //Same as using memnew

        Error err = server_peer->create_server(7654, 32);
        SceneMultiplayer* scene_multiplayer = Object::cast_to<SceneMultiplayer>(get_multiplayer().ptr());
                scene_multiplayer->set_root_path(get_path());

        ERR_FAIL_COND(!scene_multiplayer);
        
        scene_multiplayer->set_multiplayer_peer(server_peer);

        server_peer->connect("peer_connected", callable_mp(this, &Server::on_peer_connect));
        server_peer->connect("peer_disconnected", callable_mp(this, &Server::on_peer_disconnect));

        //Error err = server_peer->create_host_bound((IPAddress)("*"), server_port, 32, 3);

        if(err == Error::OK)
        {
            print_line("Server is listening on port", server_port);
        }
        else
        {
            print_line("Failed to create server! Error code: " + err);
        }
}