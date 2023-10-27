#include "server.h"
#include <server/core/s_game.h>
#include <server/networking/requests/request_handler.h>

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