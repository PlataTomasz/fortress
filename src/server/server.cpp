#include "server.h"
#include <server/core/s_game.h>

void Server::on_receive(const uint8_t *packet_data, uint64_t size)
{
    game->put_game_command(SGameCommandFactory::create(packet_data, size));
}