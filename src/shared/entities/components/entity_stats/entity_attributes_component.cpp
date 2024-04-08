#include "entity_attributes_component.h"

Ref<FloatAttribute> EntityAttributesComponent::get_current_health() {
    return current_health;
}

void EntityAttributesComponent::set_current_health(Ref<FloatAttribute> attribute) {
    current_health = attribute;
}

Ref<FloatAttribute> EntityAttributesComponent::get_max_health() {
    return max_health;
}

void EntityAttributesComponent::set_max_health(Ref<FloatAttribute> attribute) {
    max_health = attribute;
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
