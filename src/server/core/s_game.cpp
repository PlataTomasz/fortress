#include "s_game.h"

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
            fixed_tick();
        }
        break;
    
    default:
        break;
    }
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