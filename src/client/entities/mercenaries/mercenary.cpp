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

    stats.movementSpeed.set_initial_value(2);

    connect("ready", callable_mp(this, &Mercenary::initialize));
    //connect("physics_frame", callable_mp(this, &Mercenary::physics_frame));
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
   
}

Ability *Mercenary::set_ability(AbilitySetIndex abilityIndex, Ability *ability)
{
    abilitySet[abilityIndex] = ability;
    ability->set_owner(this);
}

void Mercenary::_bind_methods()
{

}

void Mercenary::physics_frame()
{
    //Ability cooldown handling
    for(int i = 0;i<Mercenary::ABILITY_MAX;i++)
    {
        
    }
}

Mercenary::~Mercenary()
{
    
}