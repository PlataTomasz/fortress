#include "fist_mercenary.hpp"
#include <client/game_logic/abilities/fist_mercenary/fist_mercenary_strafe.hpp>
#include <client/game_logic/abilities/fist_mercenary/fist_mercenary_basic_attack.hpp>
#include <gdextension_helper.hpp>

FistMercenary::FistMercenary()
{
    DISABLE_IN_EDITOR();
    abilitySet[ABILITY_FIRST] = new FistMercenaryStrafeAbility(this);

    basic_attack_ability = new FistMercenaryBasicAttackAbility(this);

    
}

void FistMercenary::_ready()
{

}

void FistMercenary::_spawn()
{

}