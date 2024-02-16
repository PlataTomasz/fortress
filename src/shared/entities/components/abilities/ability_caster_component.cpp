#include "ability_caster_component.h"
#include <shared/abilities/test_ability.hpp>
#include <shared/data_holders/use_context.hpp>
#include <shared/helper_macros.h>

#include <memory.h>

AbilityCasterComponent::AbilityCasterComponent()
{
    DISABLE_IN_EDITOR();

    set_ability(ABILITY_PASSIVE, memnew(TestAbility));
    set_ability(ABILITY_FIRST, memnew(TestAbility));
    set_ability(ABILITY_SECOND, memnew(TestAbility));
    set_ability(ABILITY_THIRD, memnew(TestAbility));
    set_ability(ABILITY_ULTIMATE, memnew(TestAbility));
}

AbilityCasterComponent::AbilityCasterComponent(Ability *abilities[ABILITY_MAX])
{
    DISABLE_IN_EDITOR();

    set_ability(ABILITY_PASSIVE, abilities[ABILITY_PASSIVE]);
    set_ability(ABILITY_FIRST, abilities[ABILITY_FIRST]);
    set_ability(ABILITY_SECOND, abilities[ABILITY_SECOND]);
    set_ability(ABILITY_THIRD, abilities[ABILITY_THIRD]);
    set_ability(ABILITY_ULTIMATE, abilities[ABILITY_ULTIMATE]);
}

void AbilityCasterComponent::_notification(int notification)
{
    switch(notification)
    {
        case NOTIFICATION_READY:
            print_line("Ready from notification! - AbilityCasterComponent");
        break;

        case NOTIFICATION_PHYSICS_PROCESS:
            tick();
        break;
    }
}

void AbilityCasterComponent::use_ability(AbilitySetIndex ability_id, UseContext use_context) {
	ERR_FAIL_COND(!(ability_id > 0 && ability_id < ability_count));
	abilitySet[ability_id]->use(use_context);
}

void AbilityCasterComponent::use_basic_attack(UseContext& use_context)
{
    basic_attack_ability->use(use_context);
}

void AbilityCasterComponent::initialize()
{

}

void AbilityCasterComponent::set_ability(AbilitySetIndex abilityIndex, Ability *ability)
{
    abilitySet[abilityIndex] = ability;
    //NOTE: Might cause crashes due to use of static_cast
    ability->set_owner(static_cast<Entity *>(this->get_parent()));
}

void AbilityCasterComponent::_bind_methods()
{

}

void AbilityCasterComponent::tick()
{
    //Ability ticking
    for(int i = 0;i<AbilityCasterComponent::ABILITY_MAX;i++)
    {
        abilitySet[i]->tick();
    }
}

AbilityCasterComponent::~AbilityCasterComponent()
{

}
