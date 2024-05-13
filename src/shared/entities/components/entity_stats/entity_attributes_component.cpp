#include "entity_attributes_component.h"

Ref<FloatAttribute> EntityAttributesComponent::get_health() {
    return health;
}

void EntityAttributesComponent::set_health(Ref<FloatAttribute> attribute) {
    health = attribute;
}

Ref<FloatAttribute> EntityAttributesComponent::get_global_defense() {
    return global_defense;
}

void EntityAttributesComponent::set_global_defense(Ref<FloatAttribute> attribute) {
    global_defense = attribute;
}

Ref<FloatAttribute> EntityAttributesComponent::get_attack_damage() {
    return attack_damage;
}

void EntityAttributesComponent::set_attack_damage(Ref<FloatAttribute> attribute) {
    attack_damage = attribute;
}

Ref<FloatAttribute> EntityAttributesComponent::get_attack_speed() {
    return attack_speed;
}

void EntityAttributesComponent::set_attack_speed(Ref<FloatAttribute> attribute) {
    attack_speed = attribute;
}

Ref<FloatAttribute> EntityAttributesComponent::get_magic_power() {
    return magic_power;
}

void EntityAttributesComponent::set_magic_power(Ref<FloatAttribute> attribute) {
    magic_power = attribute;
}

Ref<FloatAttribute> EntityAttributesComponent::get_cooldown_reduction() {
    return cooldown_reduction;
}

void EntityAttributesComponent::set_cooldown_reduction(Ref<FloatAttribute> attribute) {
    cooldown_reduction = attribute;
}

Ref<FloatAttribute> EntityAttributesComponent::get_movement_speed() {
    return movement_speed;
}

void EntityAttributesComponent::set_movement_speed(Ref<FloatAttribute> attribute) {
    movement_speed = attribute;
}


void EntityAttributesComponent::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_health"), &EntityAttributesComponent::get_health);
    ::ClassDB::bind_method(D_METHOD("set_health"), &EntityAttributesComponent::set_health);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "health", PROPERTY_HINT_RESOURCE_TYPE, "CappedResourceAttribute"), "set_health", "get_health");

    ::ClassDB::bind_method(D_METHOD("get_global_defense"), &EntityAttributesComponent::get_global_defense);
    ::ClassDB::bind_method(D_METHOD("set_global_defense"), &EntityAttributesComponent::set_global_defense);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "global_defense", PROPERTY_HINT_RESOURCE_TYPE, "FloatAttribute"), "set_global_defense", "get_global_defense");

    ::ClassDB::bind_method(D_METHOD("get_attack_damage"), &EntityAttributesComponent::get_attack_damage);
    ::ClassDB::bind_method(D_METHOD("set_attack_damage"), &EntityAttributesComponent::set_attack_damage);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attack_damage", PROPERTY_HINT_RESOURCE_TYPE, "FloatAttribute"), "set_attack_damage", "get_attack_damage");

    ::ClassDB::bind_method(D_METHOD("get_attack_speed"), &EntityAttributesComponent::get_attack_speed);
    ::ClassDB::bind_method(D_METHOD("set_attack_speed"), &EntityAttributesComponent::set_attack_speed);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attack_speed", PROPERTY_HINT_RESOURCE_TYPE, "FloatAttribute"), "set_attack_speed", "get_attack_speed");

    ::ClassDB::bind_method(D_METHOD("get_magic_power"), &EntityAttributesComponent::get_magic_power);
    ::ClassDB::bind_method(D_METHOD("set_magic_power"), &EntityAttributesComponent::set_magic_power);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "magic_power", PROPERTY_HINT_RESOURCE_TYPE, "FloatAttribute"), "set_magic_power", "get_magic_power");

    ::ClassDB::bind_method(D_METHOD("get_cooldown_reduction"), &EntityAttributesComponent::get_cooldown_reduction);
    ::ClassDB::bind_method(D_METHOD("set_cooldown_reduction"), &EntityAttributesComponent::set_cooldown_reduction);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cooldown_reduction", PROPERTY_HINT_RESOURCE_TYPE, "FloatAttribute"), "set_cooldown_reduction", "get_cooldown_reduction");

    ::ClassDB::bind_method(D_METHOD("get_movement_speed"), &EntityAttributesComponent::get_movement_speed);
    ::ClassDB::bind_method(D_METHOD("set_movement_speed"), &EntityAttributesComponent::set_movement_speed);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "movement_speed", PROPERTY_HINT_RESOURCE_TYPE, "FloatAttribute"), "set_movement_speed", "get_movement_speed");
}