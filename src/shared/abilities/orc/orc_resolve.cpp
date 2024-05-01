#include "orc_resolve.h"

#include <shared/entities/components/damage/damageable_component.h>

void OrcResolve::_tick() {
    float heal_value = 1 * get_process_delta_time();

    Node *owner = get_node_or_null(NodePath("../.."));
    ERR_FAIL_NULL(owner);

    DamageableComponent *damageable_component = ComponentManager::get_component<DamageableComponent>(owner);
    if(!damageable_component) return;
    damageable_component->heal(heal_value);
}