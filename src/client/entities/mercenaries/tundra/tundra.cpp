#include "tundra.hpp"
#include <client/game_logic/abilities/tundra/tundra_chain_lash.hpp>
#include <client/game_logic/abilities/test_ability.hpp>
#include <classes/engine.hpp>
#include <gdextension_helper.hpp>

Tundra::Tundra()
{
    DISABLE_IN_EDITOR();

    abilitySet[ABILITY_PASSIVE] = new TestAbility();
    abilitySet[ABILITY_FIRST] = new TestAbility();
    abilitySet[ABILITY_SECOND] = new TestAbility();
    abilitySet[ABILITY_THIRD] = new TestAbility();
    abilitySet[ABILITY_ULTIMATE] = new TestAbility();
}

void Tundra::_ready()
{
    DISABLE_IN_EDITOR();
    _spawn();
}

void Tundra::_spawn()
{
    printf("Tundra::onSpawn() called!\n");
    //Create ball entity
    applyStatusEffect("tundra_spiky_ball", 15, this);

}