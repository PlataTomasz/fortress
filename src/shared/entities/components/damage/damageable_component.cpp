#include "damageable_component.h"
#include <shared/string_names/component_stringnames.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/core/managers/component_manager.h>
#include <shared/core/realm.h>
#include <shared/core/sh_game.h>

#include <shared/entities/entity.h>

// TODO: Deprecated - Remove
void DamageableComponent::take_damage(Ref<DamageObject> damage_object)
{
    Entity *parent_entity = Object::cast_to<Entity>(this->get_parent());
    ERR_FAIL_NULL(parent_entity);

    EntityAttributesComponent *attributes_component = parent_entity->get_attributes_component();
    if(!attributes_component) return;

	float global_defense_val = attributes_component->get_global_defense()->get_current();

    Ref<CappedResourceAttribute> health_atr = attributes_component->get_health();
	float health_value = health_atr->get_current();

	//Reduce incoming damage with global defense - Damage reduction equation
	float damage_multiplier = 100 / (100 + global_defense_val);
	float incoming_damage = damage_multiplier * damage_object->get_value();

    health_atr->set_current(health_value - incoming_damage);

	bool was_lethal = attributes_component->get_health()->get_current() <= 0;

	emit_signal("damage_taken", damage_object);

	if (was_lethal) {
		emit_signal("death", damage_object->get_attacker(), (Node *)nullptr);
	}
}

void DamageableComponent::heal(float value) {
    Entity *ent = get_owning_entity();
    ERR_FAIL_NULL(ent);
    
    EntityAttributesComponent *attributes = ent->get_component<EntityAttributesComponent>();

    Ref<CappedResourceAttribute> health_attribute = attributes->get_health();

    float max_health = health_attribute->get_max();
    float current_health = health_attribute->get_current();

    // Make sure heal won't exceed maximum life
    float heal_value = (value + current_health) > max_health ? max_health - current_health : value;

    health_attribute->set_current(current_health + heal_value);
}

Entity *DamageableComponent::get_owning_entity() {
    return Object::cast_to<Entity>(get_parent());
}

void DamageableComponent::_bind_methods() {
    ADD_SIGNAL(MethodInfo("damage_taken", PropertyInfo(Variant::OBJECT, "damage_object")));
}