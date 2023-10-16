#include "request_handler.h"
#include <shared/networking/requests/request_types.h>
#include <server/core/game_commands/s_game_commands.h>
#include <core/io/marshalls.h>
#include <modules/enet/enet_multiplayer_peer.h>
#include <shared/io/stream_peer_reader.h>
#include <server/helpers/s_common_nodes.h>
#include <server/core/s_game.h>
#include <server/entities/s_base_entity.h>

const char *RequestHandler::ERROR_MESSAGE_INVALID_SIZE = "Invalid data size! Request discarded!";

void RequestHandler::handle_request(Ref<ENetPacketPeer> sender, const uint8_t *requst_data, uint64_t size)
{
    S_Player *ply = get_game_server()->get_player_by_peer(sender);

    const uint8_t header = *requst_data;
    const uint8_t *headerless_data = requst_data + 1;
    const uint64_t data_size = size - 1;

    switch (header)
    {
    case Request::Type::CLIENT_CONNECT:
    {
        StreamPeerReader buffer(headerless_data, data_size);
        String player_name = buffer.get_string();

        //Server Player init
    }
    break;

    case Request::Type::MOVEMENT:
    {
        ERR_FAIL_COND_MSG(data_size < 16, RequestHandler::ERROR_MESSAGE_INVALID_SIZE);
        StreamPeerReader byte_reader(headerless_data, data_size);

        uint64_t ent_netid = byte_reader.get_u64();
        S_BaseEntity *ent = get_game_server()->get_game()->get_entity_by_netid(ent_netid);
        S_LivingEntity *issuer = Object::cast_to<S_LivingEntity>(ply->get_controlled_entity());

        Vector2 pos(byte_reader.get_float(), byte_reader.get_float());

        ERR_FAIL_COND_MSG(!ent, "Entity is immovable");
        S_GameCommand *gamecmd = new S_GameCommandMovement(issuer, ent, pos);
    }
    break;
    
    default:
        break;
    }
}