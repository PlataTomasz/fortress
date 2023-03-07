#include <client/entities/mercenaries/mercenary.hpp>
#include <client/game_logic/abilities/test_ability.hpp>
#include <client/game_logic/abilities/use_context.hpp>
#include <gdextension_helper.hpp>

Mercenary::Mercenary()
{
    DISABLE_IN_EDITOR();

    abilitySet[0] = new TestAbility();
    abilitySet[1] = new TestAbility();
    abilitySet[2] = new TestAbility();
    abilitySet[3] = new TestAbility();
    abilitySet[4] = new TestAbility();

    connect("ready", Callable(this, "initialize"));
}

void Mercenary::use_ability(int ability_id, UseContext use_context)
{
    abilitySet[ability_id]->use(use_context);
}

void Mercenary::use_basic_attack(UseContext use_context)
{
    basic_attack_ability->use(use_context);
}

void Mercenary::initialize()
{
    //Initialize abilities
    basic_attack_ability->initialize();

    abilitySet[ABILITY_PASSIVE]->initialize();
    abilitySet[ABILITY_FIRST]->initialize();
    abilitySet[ABILITY_SECOND]->initialize();
    abilitySet[ABILITY_THIRD]->initialize();
    abilitySet[ABILITY_ULTIMATE]->initialize();
}

void Mercenary::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("initialize"), &Mercenary::initialize);
}

Mercenary::~Mercenary()
{
    
}