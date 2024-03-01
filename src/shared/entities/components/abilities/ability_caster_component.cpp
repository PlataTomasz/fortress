#include "ability_caster_component.h"
#include <shared/abilities/test_ability.hpp>
#include <shared/data_holders/use_context.hpp>
#include <shared/helper_macros.h>

#include <memory.h>

AbilityCasterComponent::AbilityCasterComponent()
{
    DISABLE_IN_EDITOR();
}

void AbilityCasterComponent::_notification(int p_notification)
{

}

void AbilityCasterComponent::_bind_methods()
{

}

AbilityCasterComponent::~AbilityCasterComponent()
{

}

Error AbilityCasterComponent::use_ability(int index, Dictionary use_context) {
    ERR_FAIL_COND(index >= get_child_count());
    Ability *ability = static_cast<Ability *>(get_child(index, false));
    ability->use(use_context);
}