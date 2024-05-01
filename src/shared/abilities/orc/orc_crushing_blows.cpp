#include "orc_crushing_blows.h"

#include <shared/core/managers/component_manager.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/registries/status_effect_registry.h>

void OrcCrushingBlows::_use(const Ref<ActionContext> &action_context) {
    Node *owner = get_node_or_null(NodePath("../.."));
    ERR_FAIL_NULL(owner);

    StatusEffectVictimComponent *status_effect_victim = ComponentManager::get_component<StatusEffectVictimComponent>(owner);

    if(status_effect_victim) {
        //OrcCrushingBlowsStatusEffect *crushing_blows_status = ;
        StatusEffect *crushing_blows_status = StatusEffectRegistry::get_singleton()->create_instance("OrcCrushingBlowsBuff");
        ERR_FAIL_NULL(crushing_blows_status);
    }
}