#include "tundra.hpp"
#include "../../../game_logic/abilities/test_ability.hpp"
#include "../../../game_logic/abilities/tundra/tundra_chain_lash.hpp"
#include <classes/engine.hpp>

Tundra::Tundra()
{
    if(!Engine::get_singleton()->is_editor_hint())
    {
        skillSet[ABILITY_PASSIVE] = new TestAbility();
        skillSet[ABILITY_FIRST] = new TundraChainLashAbility();
        skillSet[ABILITY_SECOND] = new TestAbility();
        skillSet[ABILITY_THIRD] = new TestAbility();
        skillSet[ABILITY_ULTIMATE] = new TestAbility();

        //TODO: Find alternative for callable_mp
        //connect("ready", callable_mp(this, &Tundra::onReady));
    }
}

void Tundra::onReady()
{
    onSpawn();
}

void Tundra::onSpawn()
{
    printf("Tundra::onSpawn() called!\n");
    //Create ball entity
    applyStatusEffect("tundra_spiky_ball", 15, this);

    
}