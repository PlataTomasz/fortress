#include "damageable_component.h"
#include <shared/string_names/component_stringnames.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/core/managers/component_manager.h>
#include <shared/core/realm.h>
#include <shared/core/sh_game.h>

#include <shared/entities/traits/t_has_attributes.h>

// TODO: Deprecated - Remove
void DamageableComponent::take_damage(Ref<DamageObject> damage_object)
{
    //Check if entity has component responsible for attributes

    Entity *ent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_NULL(ent);
    //EntityAttributesComponent *attributes_component = ent->get_component<EntityAttributesComponent>();
    //ERR_FAIL_NULL(attributes_component);

    //Apply modifiers
    emit_signal("pre_take_damage", damage_object);
    //Entity took damage and now it applies mitigation rules
    emit_signal("on_take_damage", damage_object);

    //Ref<Stat> health = stat_component.health;
    //Ref<Stat> defense = stat_component.global_defense;

    //Damage formula here

    emit_signal("post_take_damage", damage_object);
}

void DamageableComponent::take_damage(float damage_value, Node *inflictor, Node *caused_by) {
    THasAttributes *t_has_attributes = dynamic_cast<THasAttributes *>(get_parent());
    if(!t_has_attributes) return;

    EntityAttributesComponent *attributes_component = t_has_attributes->get_attributes_component();
    if(!attributes_component) return;

	float global_defense_val = attributes_component->get_global_defense()->get_current();

    Ref<CappedResourceAttribute> health_atr = attributes_component->get_health();
	float health_value = health_atr->get_current();

	//Reduce incoming damage with global defense - Damage reduction equation
	float damage_multiplier = global_defense_val / (100 + global_defense_val);
	float incoming_damage = damage_multiplier * damage_value;

    health_atr->set_current(health_value - incoming_damage);

	bool was_lethal = attributes_component->get_health()->get_current() <= 0;

	emit_signal("damage_taken", damage_value, inflictor, caused_by, was_lethal);

	if (was_lethal) {
		emit_signal("death", inflictor, caused_by);
	}
}

void DamageableComponent::heal(float value) {
    THasAttributes *t_has_attributes = dynamic_cast<THasAttributes *>(get_parent());
    if(!t_has_attributes) return;

    EntityAttributesComponent *attributes_component = t_has_attributes->get_attributes_component();
    if(!attributes_component) return;

    Ref<CappedResourceAttribute> health_attribute = attributes_component->get_health();

    float max_health = health_attribute->get_max();
    float current_health = health_attribute->get_current();

    // Make sure heal won't exceed maximum life
    float heal_value = (value + current_health) > max_health ? max_health - current_health : value;

    health_attribute->set_current(current_health + heal_value);
}