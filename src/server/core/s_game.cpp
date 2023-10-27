#include "s_game.h"
#include <server/server.h>

S_Game::S_Game()
{
    set_physics_process(true);

    Dictionary movement_request_rpc_cfg;
    movement_request_rpc_cfg["rpc_mode"] = MultiplayerAPI::RPC_MODE_ANY_PEER;
    movement_request_rpc_cfg["channel"] = 0;
    movement_request_rpc_cfg["call_local"] = false;
    movement_request_rpc_cfg["transfer_mode"] = MultiplayerPeer::TRANSFER_MODE_RELIABLE;
    rpc_config("movement_request", movement_request_rpc_cfg);
}

void S_Game::_notification(int notification)
{
    switch (notification)
    {
    case NOTIFICATION_PHYSICS_PROCESS:
        {
            //Process next server tick
            fixed_tick();



            //Update clients
            sync_gamestate();
        }
        break;

    case NOTIFICATION_ENTER_TREE:
        {
            server = static_cast<Server *>(get_parent());
        }
        break;
    
    default:
        break;
    }
}

void S_Game::sync_gamestate()
{
    String sync_data = "Gamestate sync!";
    PackedByteArray bytes = sync_data.to_utf8_buffer();
    server->send_data_to_all(bytes.ptr(), bytes.size());

    
}

void S_Game::fixed_tick()
{
    //Dispatch game commands
    for(auto cmd : game_commands)
    {
        cmd->execute(this);
        delete cmd;
    }

    game_commands.clear();
}

void S_Game::put_game_command(S_GameCommand *gamecmd)
{
    game_commands.push_back(gamecmd);
}

Error S_Game::serialize_gamestate(uint8_t *p_data, uint64_t size)
{
    

    return Error::OK;
}

S_BaseEntity *S_Game::get_entity_by_netid(uint64_t netid)
{
    ERR_FAIL_COND_V(!networked_entities.has(netid), nullptr);
    
    return networked_entities.get(netid);
}

void S_Game::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("movement_request", "target_position"), &S_Game::movement_request);
}

void S_Game::movement_request(Vector2 target_pos)
{
    print_line("Movement request!", target_pos);
}