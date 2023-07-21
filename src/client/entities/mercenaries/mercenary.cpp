#include <client/entities/mercenaries/mercenary.hpp>
#include <client/game_logic/abilities/test_ability.hpp>
#include <client/game_logic/abilities/use_context.hpp>
#include <gdextension_helper.hpp>

Mercenary::Mercenary()
{
    DISABLE_IN_EDITOR();
    
    set_ability(ABILITY_PASSIVE, memnew(TestAbility));
    set_ability(ABILITY_FIRST, memnew(TestAbility));
    set_ability(ABILITY_SECOND, memnew(TestAbility));
    set_ability(ABILITY_THIRD, memnew(TestAbility));
    set_ability(ABILITY_ULTIMATE, memnew(TestAbility));
    
    stats.movementSpeed.set_initial_value(2);

    connect("ready", callable_mp(this, &Mercenary::initialize));
    //connect("physics_frame", callable_mp(this, &Mercenary::physics_frame));
}

void Mercenary::use_ability(AbilitySetIndex ability_id, UseContext use_context)
{
    print_line(abilitySet[ability_id]->get_instance_id());
    abilitySet[ability_id]->use(use_context);
}

void Mercenary::use_basic_attack(UseContext& use_context)
{
    basic_attack_ability->use(use_context);
}

void Mercenary::initialize()
{
   
}

void Mercenary::set_ability(AbilitySetIndex abilityIndex, Ability *ability)
{
    abilitySet[abilityIndex] = ability;
    print_line(ability->get_class_static());
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