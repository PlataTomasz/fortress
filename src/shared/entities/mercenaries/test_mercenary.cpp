#include "test_mercenary.hpp"
#include <client/game_logic/abilities/test_ability.hpp>

TestMercenary::TestMercenary()
{
    //Setup abilities
    abilitySet[0] = new TestAbility();
    abilitySet[1] = new TestAbility();
    abilitySet[2] = new TestAbility();
    abilitySet[3] = new TestAbility();
    abilitySet[4] = new TestAbility();
}

TestMercenary::~TestMercenary()
{
    
}