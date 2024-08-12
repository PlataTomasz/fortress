#include "entity.h"
#include <game.h>

#include <shared/entities/components/component.h>
#include <shared/core/managers/component_manager.h>
#include <shared/core/game_level.h>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/entities/components/movement/movement_component.h>

bool Entity::has_tag(const String& tag) {
	return is_in_group(tag);
}

void Entity::add_tag(const String& tag) {
	add_to_group(tag);
}

void Entity::remove_tag(const String& tag) {
	remove_from_group(tag);
}

bool Entity::has_tag(const String& tag) {
	return is_in_group(tag);
}

void Entity::add_tag(const String& tag) {
	add_to_group(tag);
}

void Entity::remove_tag(const String& tag) {
	remove_from_group(tag);
}

void Entity::_bind_methods() {
	ADD_SIGNAL(MethodInfo("hit_taken", PropertyInfo(Variant::OBJECT, "inflictor"), PropertyInfo(Variant::OBJECT, "attacker")));
	ADD_SIGNAL(MethodInfo("displayed_name_changed", PropertyInfo(Variant::STRING, "new_displayed_name")));

	::ClassDB::bind_method(D_METHOD("get_displayed_name"), &Entity::get_displayed_name);
    ::ClassDB::bind_method(D_METHOD("set_displayed_name"), &Entity::set_displayed_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_name"), "set_displayed_name", "get_displayed_name");

	::ClassDB::bind_method(D_METHOD("get_status_effect_victim_component"), &Entity::get_status_effect_victim_component);
    ::ClassDB::bind_method(D_METHOD("set_status_effect_victim_component"), &Entity::set_status_effect_victim_component);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "status_effect_victim_component", PROPERTY_HINT_NODE_TYPE, StatusEffectVictimComponent::get_class_static()), "set_status_effect_victim_component", "get_status_effect_victim_component");

    ::ClassDB::bind_method(D_METHOD("get_damageable_component"), &Entity::get_damageable_component);
    ::ClassDB::bind_method(D_METHOD("set_damageable_component"), &Entity::set_damageable_component);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "damageable_component", PROPERTY_HINT_NODE_TYPE, DamageableComponent::get_class_static()), "set_damageable_component", "get_damageable_component");

	::ClassDB::bind_method(D_METHOD("get_attributes_component"), &Entity::get_attributes_component);
    ::ClassDB::bind_method(D_METHOD("set_attributes_component"), &Entity::set_attributes_component);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attributes_component", PROPERTY_HINT_NODE_TYPE, EntityAttributesComponent::get_class_static()), "set_attributes_component", "get_attributes_component");

	::ClassDB::bind_method(D_METHOD("get_ability_caster_component"), &Entity::get_ability_caster_component);
    ::ClassDB::bind_method(D_METHOD("set_ability_caster_component"), &Entity::set_ability_caster_component);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ability_caster_component", PROPERTY_HINT_NODE_TYPE, AbilityCasterComponent::get_class_static()), "set_ability_caster_component", "get_ability_caster_component");

	::ClassDB::bind_method(D_METHOD("get_movement_component"), &Entity::get_movement_component);
    ::ClassDB::bind_method(D_METHOD("set_movement_component"), &Entity::set_movement_component);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "movement_component", PROPERTY_HINT_NODE_TYPE, MovementComponent::get_class_static()), "set_movement_component", "get_movement_component");

}

Node *Entity::_get_component(const String& component_typename) {
	return nullptr;
}

void Entity::_tick() {

}

GameLevel *Entity::get_gamelevel() {
	// FIXME: Will break if "Entity" node on GameLevel is not at 1 level of ident
	return Object::cast_to<GameLevel>(get_parent()->get_parent());
}

void Entity::_init() {
	DISABLE_IN_EDITOR();
	set_process(true);
	set_physics_process(true);
}

void Entity::_ready() {
	DISABLE_IN_EDITOR();
}

void Entity::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			_readyv();
			break;
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			_initv();
			break;
		case NOTIFICATION_PHYSICS_PROCESS:
			_tickv();
			break;

		default:
			break;
	}
}

StatusEffectVictimComponent *Entity::get_status_effect_victim_component() {
	return status_effect_victim_component;
}

void Entity::set_status_effect_victim_component(StatusEffectVictimComponent *new_status_effect_vicitm_component) {
	status_effect_victim_component = new_status_effect_vicitm_component;
}

DamageableComponent *Entity::get_damageable_component() {
	return damageable_component;
}

void Entity::set_damageable_component(DamageableComponent *new_damageable_component) {
	damageable_component = new_damageable_component;
}

AbilityCasterComponent *Entity::get_ability_caster_component() {
	return ability_caster_component;
}

void Entity::set_ability_caster_component(AbilityCasterComponent *new_ability_caster_component) {
	ability_caster_component = new_ability_caster_component;
}

EntityAttributesComponent *Entity::get_attributes_component() {
	return attributes_component;
}

void Entity::set_attributes_component(EntityAttributesComponent *new_attributes_component) {
	attributes_component = new_attributes_component;
}

MovementComponent *Entity::get_movement_component() {
	return movement_component;
}

void Entity::set_movement_component(MovementComponent *new_movement_component) {
	movement_component = new_movement_component;
}
