#include "orc_resolve.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <scene/main/timer.h>

void OrcResolve::_tick() {
    print_line("Heal tick!");
    float heal_value = 1;

    Entity *owner = Object::cast_to<Entity>(get_node_or_null(NodePath("../..")));
    ERR_FAIL_NULL(owner);

    //DamageableComponent *damageable_component = ComponentManager::get_component<DamageableComponent>(owner);
    DamageableComponent *damageable = owner->get_damageable_component();
    if(!damageable) return;
    damageable->heal(heal_value);
}

void OrcResolve::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        {
            Timer *timer = memnew(Timer);
            timer->set_wait_time(1.0);
            timer->set_autostart(true);
            add_child(timer);

            timer->connect("timeout", callable_mp(this, &OrcResolve::_tick));
        }
        break;
    default:
        break;
    }
}