#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>

void DamageableComponent::server_rpc_death() {
    ERR_FAIL_MSG("Not implemented!");
}

void DamageableComponent::server_rpc_revive() {
    ERR_FAIL_MSG("Not implemented!");
}

void DamageableComponent::revive() {
    Entity *parent_entity = Object::cast_to<Entity>(this->get_parent());
    ERR_FAIL_NULL(parent_entity);

    EntityAttributesComponent *attributes_component = parent_entity->get_attributes_component();
    if(!attributes_component) return;

    // Restore health to maximum
    heal(attributes_component->get_health()->get_max());

    set_dead(false);
    rpc("server_rpc_revive");
    emit_signal("revived");
}