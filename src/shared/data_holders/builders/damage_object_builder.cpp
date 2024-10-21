#include "damage_object_builder.h"

DamageObjectBuilder &DamageObjectBuilder::damage_type(DamageObject::DamageType new_type) {
    _damage_type = new_type;
    return *this;
}

DamageObjectBuilder &DamageObjectBuilder::damage_subtype_basic_attack() {
    _damage_subtype |= DamageObject::DamageSubtype::BASIC_ATTACK_DAMAGE;
    return *this;
}

DamageObjectBuilder &DamageObjectBuilder::damage_subtype_ability() {
    _damage_subtype |= DamageObject::DamageSubtype::ABILITY_DAMAGE;
    return *this;
}

DamageObjectBuilder &DamageObjectBuilder::damage_subtype_area() {
    _damage_subtype |= DamageObject::DamageSubtype::AREA_DAMAGE;
    return *this;
}

DamageObjectBuilder &DamageObjectBuilder::damage_subtype_self() {
    _damage_subtype |= DamageObject::DamageSubtype::SELF_DAMAGE;
    return *this;
}

DamageObjectBuilder &DamageObjectBuilder::damage_subtype_over_time() {
    _damage_subtype |= DamageObject::DamageSubtype::OVER_TIME_DAMAGE;
    return *this;
}

DamageObjectBuilder &DamageObjectBuilder::value(float new_value) {
    _damage_value = new_value;
    return *this;
}

DamageObjectBuilder &DamageObjectBuilder::attacker(Entity *new_attacker) {
    _attacker = new_attacker;
    return *this;
}

DamageObject *DamageObjectBuilder::build() {
    return memnew(DamageObject(
        _damage_type,
        _damage_subtype,
        _damage_value,
        _attacker
    ));
}