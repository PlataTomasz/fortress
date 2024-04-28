#include "ability_caster_component.h"
#include <shared/abilities/test_ability.hpp>
#include <shared/data_holders/action_context.hpp>
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

Ability::AbilityUseError AbilityCasterComponent::use_ability(int index, const Ref<ActionContext>& action_context) {
    ERR_FAIL_COND_V(index >= get_child_count(), Ability::AbilityUseError::INTERNAL_ERROR);
    Ability *ability = static_cast<Ability *>(get_child(index, false));
    return ability->use(action_context);
}