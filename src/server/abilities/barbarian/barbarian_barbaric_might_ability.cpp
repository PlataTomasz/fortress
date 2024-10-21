#include <shared/abilities/barbarian/barbarian_barbaric_might_ability.h>

#include <shared/status_effects/status_effect.hpp>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/registries/status_effect_registry.h>

void BarbarianBarbaricMightAbility::_use(const Ref<ActionContext> &use_context) {
    // Grant status effect
    ERR_FAIL_NULL(use_context->get_user());

    StatusEffectVictimComponent *status_effect_component = use_context->get_user()->get_status_effect_victim_component();
    ERR_FAIL_NULL(status_effect_component);

    StatusEffect *status_effect = StatusEffectRegistry::get_singleton()->create_instance("barbarian_barbaric_might_buff");
    ERR_FAIL_NULL(status_effect);

    status_effect->set_inflictor(use_context->get_user());

    status_effect_component->apply_status_effect(status_effect);
}