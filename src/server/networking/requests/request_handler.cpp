#include "request_handler.h"
#include <shared/networking/requests/request_types.h>
#include <server/core/game_commands/s_game_commands.h>
#include <core/io/marshalls.h>
#include <modules/enet/enet_multiplayer_peer.h>
#include <shared/io/stream_peer_reader.h>
#include <server/helpers/s_common_nodes.h>
#include <server/core/s_game.h>
#include <server/entities/s_base_entity.h>

void RequestHandler::movement_request(Vector2 target_position)
{
    //FIXME: Placeholder nullptrs
    get_game_server()->get_game()->put_game_command(new S_GameCommandMovement(nullptr, nullptr, target_position));
}

void RequestHandler::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("movement_request", "position"), &RequestHandler::movement_request);
}

RequestHandler::RequestHandler()
{
    Dictionary movement_request_rpc_cfg;
    movement_request_rpc_cfg["rpc_mode"] = MultiplayerAPI::RPC_MODE_AUTHORITY;
    movement_request_rpc_cfg["channel"] = 0;
    movement_request_rpc_cfg["call_local"] = false;
    movement_request_rpc_cfg["transfer_mode"] = MultiplayerPeer::TRANSFER_MODE_UNRELIABLE;
    rpc_config("movement_request", movement_request_rpc_cfg);
}

