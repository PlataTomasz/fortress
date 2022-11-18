#include "mercenary.hpp"
#include "../../game_logic/abilities/test_ability.hpp"

Mercenary::Mercenary()
{
    skillSet[0] = new TestAbility();
    skillSet[1] = new TestAbility();
    skillSet[2] = new TestAbility();
    skillSet[3] = new TestAbility();
    skillSet[4] = new TestAbility();
}

void Mercenary::castAbility(int abilityId)
{
    skillSet[abilityId]->onCast();
}

Mercenary::~Mercenary()
{
    
}