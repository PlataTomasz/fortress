#include "s_game_commands.h"
#include <server/core/s_game.h>
#include <server/entities/s_living_entity.h>

//Movement request from player
void S_GameCommandMovement::execute(S_Game *game)
{
    ERR_FAIL_COND_MSG(!ent, "S_GameCommandMovement: Invalid entity!");

    print_line("Player", "[1]", "wants to move to", new_position, "from", "[old_position]");
    
    ent->set_movement_target_position(new_position);
}

S_GameCommandMovement::S_GameCommandMovement(S_BaseEntity *p_issuer, S_LivingEntity *p_ent, Vector2 p_new_position)
{
    new_position = p_new_position;
}