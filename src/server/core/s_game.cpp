#include "s_game.h"
#include <server/server.h>

S_Game::S_Game()
{
    set_physics_process(true);
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
    //Update clients
    uint8_t *data;
    uint64_t size;

    serialize_gamestate(data, size);

    /*
    server->send_data_to_all(data, size);
    */
}

void S_Game::put_game_command(S_GameCommand *gamecmd)
{
    game_commands.push_back(gamecmd);
}

Error S_Game::serialize_gamestate(uint8_t *data, uint64_t size)
{
    

    return Error::OK;
}

S_BaseEntity *S_Game::get_entity_by_netid(uint64_t netid)
{
    ERR_FAIL_COND_V(!networked_entities.has(netid), nullptr);
    
    return networked_entities.get(netid);
}