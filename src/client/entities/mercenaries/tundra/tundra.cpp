#include "tundra.hpp"
#include "../../../game_logic/abilities/test_ability.hpp"
#include "../../../game_logic/abilities/tundra/tundra_chain_lash.hpp"

Tundra::Tundra()
{
    skillSet[ABILITY_PASSIVE] = new TestAbility();
    skillSet[ABILITY_FIRST] = new TundraChainLashAbility();
    skillSet[ABILITY_SECOND] = new TestAbility();
    skillSet[ABILITY_THIRD] = new TestAbility();
    skillSet[ABILITY_ULTIMATE] = new TestAbility();
}

void Tundra::onSpawn()
{
    //Create ball entity
    
}