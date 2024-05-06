#include "orc_resolve.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/traits/t_damageable.h>

void OrcResolve::_tick() {
    print_line("Heal tick!");
    float heal_value = 1 * get_process_delta_time();

    Node *owner = get_node_or_null(NodePath("../.."));
    ERR_FAIL_NULL(owner);

    //DamageableComponent *damageable_component = ComponentManager::get_component<DamageableComponent>(owner);
    TDamageable *damageable = dynamic_cast<TDamageable *>(owner);
    if(!damageable) return;
    damageable->heal(heal_value);
}

void OrcResolve::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        set_physics_process(true);
        break;

    case NOTIFICATION_PHYSICS_PROCESS:
        _tick();
        break;
    
    default:
        break;
    }
}