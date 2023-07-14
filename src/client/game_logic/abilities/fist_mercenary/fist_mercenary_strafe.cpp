#include "fist_mercenary_strafe.hpp"

void FistMercenaryStrafeAbility::use_impl(UseContext use_context)
{
    Entity* user = use_context.get_user();
    Vector2 facing_direction = user->get_facing_direction();
    
    //Vector3 new_pos = use_context.get_target_position();

    user->set_position(use_context.get_target_position());

    //TODO: Play animation
}

FistMercenaryStrafeAbility::FistMercenaryStrafeAbility()
{

}