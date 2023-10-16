#include "game_packet_handler.h"

namespace GamePacket
{
    enum Type : uint8_t
    {
        UNDEFINED = 0,
        GAMESTATE_SYNC
    };
};

void GamePacketHandler::handle_game_packet(Ref<ENetPacketPeer> sender, const uint8_t *data, uint64_t size)
{
    const uint8_t header = *data;
    const uint8_t *headerless_data = data + 1;
    const uint64_t data_size = size - 1;

    switch (header)
    {
    case GamePacket::Type::GAMESTATE_SYNC:
    {
        
    }
    break;
    
    default:
        break;
    }
}