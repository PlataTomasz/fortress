#include "gamestate.h"
#include <server/core/s_game.h>
#include <server/entities/s_base_entity.h>

GamestateSnapshot::GamestateSnapshot(S_Game *game)
{
	/*
	frame = Engine::get_singleton()->get_physics_frames();

    S_GameLevel *map = game->get_current_level();
	TypedArray<S_BaseEntity *> map_entities = map->get_entities();

    for(int i = 0;i<map_entities.size();i++)
    {
        //Get entity netid and store it in gamestate internal hashmap
        //get_netid(ent);
		//Variant dispatch
		S_BaseEntity *ent = static_cast<S_BaseEntity *>(map_entities[i].operator Object *());

		uint8_t netid;


		entity_data[netid] = ;
		ent->get_networked_properties();
		for()
    }
	*/
}

GamestateDelta GamestateSnapshot::get_delta(GamestateSnapshot& other)
{
	GamestateDelta gamestate_delta;
	return gamestate_delta;
}
