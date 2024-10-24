#include <shared/abilities/orc/orc_resolve.h>

#include <shared/entities/components/damage/damageable_component.h>

void OrcResolve::_tick() {
    float heal_value = 1;

    Entity *owner = Object::cast_to<Entity>(get_node_or_null(NodePath("../..")));
    ERR_FAIL_NULL(owner);

    //DamageableComponent *damageable_component = ComponentManager::get_component<DamageableComponent>(owner);
    DamageableComponent *damageable = owner->get_damageable_component();
    if(!damageable || damageable->is_dead()) return;
    damageable->heal(heal_value);
}