#include <shared/abilities/orc/orc_crushing_blows.h>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/registries/status_effect_registry.h>

void OrcCrushingBlows::_use(const Ref<ActionContext> &action_context) {
    ERR_FAIL_NULL(action_context->get_user());

    StatusEffectVictimComponent *status_effect_victim = action_context->get_user()->get_status_effect_victim_component();
    ERR_FAIL_NULL(status_effect_victim);

    StatusEffect *crushing_blows_status = StatusEffectRegistry::get_singleton()->create_instance("orc_crushing_blows_buff");
    ERR_FAIL_NULL(crushing_blows_status);

    crushing_blows_status->set_inflictor(action_context->get_user());

    status_effect_victim->apply_status_effect(crushing_blows_status);
}