#include "damageable_component.h"
#include <shared/string_names/component_stringnames.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/core/managers/component_manager.h>

// TODO: Deprecated - Remove
void DamageableComponent::take_damage(Ref<DamageObject> damage_object)
{
    //Check if entity has component responsible for attributes

    Entity *ent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_NULL(ent);
    EntityAttributesComponent *attributes_component = ent->get_component<EntityAttributesComponent>();
    ERR_FAIL_NULL(attributes_component);

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
    EntityAttributesComponent *attributes_component = ComponentManager::get_component<EntityAttributesComponent>(get_parent());
	float global_defense_val = attributes_component->get_global_defense()->get_total();

	float health_value = attributes_component->get_current_health()->get_total();

	//Reduce incoming damage with global defense - Damage reduction equation
	float damage_multiplier = global_defense_val / (100 + global_defense_val);
	float incoming_damage = damage_multiplier * damage_value;
	Ref<FloatValueModifier> health_modifier = memnew(FloatValueModifier);
	health_modifier->set_type(FloatValueModifier::Type::FLAT_ADD);
	health_modifier->set_value(-health_modifier->get_value());

	bool was_lethal = attributes_component->get_current_health()->get_total() <= 0;

	emit_signal("damage_taken", damage_value, inflictor, caused_by, was_lethal);

	if (was_lethal) {
		emit_signal("death", inflictor, caused_by);
	}
}