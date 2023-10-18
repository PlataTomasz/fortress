#include "gamestate.h"
#include <server/core/s_game.h>

GamestateSnapshot::GamestateSnapshot(S_Game *game)
{
    S_GameLevel *map = game->get_current_level();

    List<S_BaseEntity *> map_entities = map->get_entities();

    for(S_BaseEntity *ent : map_entities)
    {
        //Get entity netid and store it in gamestate internal hashmap
        //get_netid(ent);
    }
}