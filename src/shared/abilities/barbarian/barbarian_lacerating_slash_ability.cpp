#include "barbarian_lacerating_slash_ability.h"
#include <scene/3d/physics/area_3d.h>


void BarbarianLaceratingSlashAbility::set_slash_area(Area3D *new_slash_area) {
    slash_area = new_slash_area;
}

Area3D *BarbarianLaceratingSlashAbility::get_slash_area() {
    return slash_area;
}

void BarbarianLaceratingSlashAbility::set_sword_swing_sound(const Ref<AudioStream> &new_sword_swing_sound) {
    sword_swing_sound = new_sword_swing_sound;
}

Ref<AudioStream> BarbarianLaceratingSlashAbility::get_sword_swing_sound() {
    return sword_swing_sound;
}

void BarbarianLaceratingSlashAbility::set_slash_area_vfx(const Ref<PackedScene> &new_slash_area_vfx) {
    slash_area_vfx = new_slash_area_vfx;
}

Ref<PackedScene> BarbarianLaceratingSlashAbility::get_slash_area_vfx() {
    return slash_area_vfx;
}

void BarbarianLaceratingSlashAbility::set_slash_hit_vfx(const Ref<PackedScene> &new_slash_hit_vfx) {
    slash_hit_vfx = new_slash_hit_vfx;
}

Ref<PackedScene> BarbarianLaceratingSlashAbility::get_slash_hit_vfx() {
    return slash_hit_vfx;
}

void BarbarianLaceratingSlashAbility::set_base_damage(float new_base_damage) {
    base_damage = new_base_damage;
}

float BarbarianLaceratingSlashAbility::get_base_damage() {
    return base_damage;
}

void BarbarianLaceratingSlashAbility::set_hit_sound(const Ref<AudioStream> &new_hit_sound) {
    hit_sound = new_hit_sound;
}

Ref<AudioStream> BarbarianLaceratingSlashAbility::get_hit_sound() {
    return hit_sound;
}

void BarbarianLaceratingSlashAbility::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_base_damage"), &BarbarianLaceratingSlashAbility::get_base_damage);
    ClassDB::bind_method(D_METHOD("set_base_damage", "base_damage"), &BarbarianLaceratingSlashAbility::set_base_damage);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "base_damage"), "set_base_damage", "get_base_damage");

    ClassDB::bind_method(D_METHOD("get_slash_area"), &BarbarianLaceratingSlashAbility::get_slash_area);
    ClassDB::bind_method(D_METHOD("set_slash_area", "slash_area"), &BarbarianLaceratingSlashAbility::set_slash_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "slash_area", PROPERTY_HINT_NODE_TYPE, Area3D::get_class_static()), "set_slash_area", "get_slash_area");

    ClassDB::bind_method(D_METHOD("get_sword_swing_sound"), &BarbarianLaceratingSlashAbility::get_sword_swing_sound);
    ClassDB::bind_method(D_METHOD("set_sword_swing_sound", "sword_swing_sound"), &BarbarianLaceratingSlashAbility::set_sword_swing_sound);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sword_swing_sound", PROPERTY_HINT_RESOURCE_TYPE, AudioStream::get_class_static()), "set_sword_swing_sound", "get_sword_swing_sound");

    ClassDB::bind_method(D_METHOD("get_hit_sound"), &BarbarianLaceratingSlashAbility::get_hit_sound);
    ClassDB::bind_method(D_METHOD("set_hit_sound", "hit_sound"), &BarbarianLaceratingSlashAbility::set_hit_sound);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hit_sound", PROPERTY_HINT_RESOURCE_TYPE, AudioStream::get_class_static()), "set_hit_sound", "get_hit_sound");

    ClassDB::bind_method(D_METHOD("get_slash_hit_vfx"), &BarbarianLaceratingSlashAbility::get_slash_hit_vfx);
    ClassDB::bind_method(D_METHOD("set_slash_hit_vfx", "slash_hit_vfx"), &BarbarianLaceratingSlashAbility::set_slash_hit_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "slash_hit_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_slash_hit_vfx", "get_slash_hit_vfx");

    ClassDB::bind_method(D_METHOD("get_slash_area_vfx"), &BarbarianLaceratingSlashAbility::get_slash_area_vfx);
    ClassDB::bind_method(D_METHOD("set_slash_area_vfx", "slash_area_vfx"), &BarbarianLaceratingSlashAbility::set_slash_area_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "slash_area_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_slash_area_vfx", "get_slash_area_vfx");
}