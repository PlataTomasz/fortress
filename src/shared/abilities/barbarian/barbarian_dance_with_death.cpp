#include "barbarian_dance_with_death.h"

#include <shared/registries/status_effect_registry.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>

Ability::AbilityUseError BarbarianDanceWithDeath::use(const Ref<ActionContext>& action_context) {
    Entity *ent = action_context->get_user();
    
    StatusEffectVictimComponent *status_effect_component = ent->get_component<StatusEffectVictimComponent>();
    ERR_FAIL_NULL_V(status_effect_component, Ability::AbilityUseError::INTERNAL_ERROR);

    StatusEffect *status_effect = Registry<StatusEffect>::get_singleton()->create_instance("dance_with_death");
    ERR_FAIL_NULL_V(status_effect, Ability::AbilityUseError::INTERNAL_ERROR);
    status_effect_component->apply_status_effect(status_effect);

    return Ability::AbilityUseError::SUCCESS;
}