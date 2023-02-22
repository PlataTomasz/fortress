#include <client/entities/mercenaries/mercenary.hpp>
#include <client/game_logic/abilities/test_ability.hpp>
#include <client/game_logic/abilities/use_context.hpp>

Mercenary::Mercenary()
{
    abilitySet[0] = new TestAbility();
    abilitySet[1] = new TestAbility();
    abilitySet[2] = new TestAbility();
    abilitySet[3] = new TestAbility();
    abilitySet[4] = new TestAbility();
}

void Mercenary::use_ability(int ability_id, UseContext use_context)
{
    abilitySet[ability_id]->use(use_context);
}

Mercenary::~Mercenary()
{
    
}