#include "orc_brute_force.h"

#include <scene/3d/physics/area_3d.h>
#include <scene/3d/physics/collision_shape_3d.h>
#include <scene/resources/3d/box_shape_3d.h>
#include <shared/entities/components/damage/damageable_component.h>

void OrcBruteForce::set_brute_force_area(Area3D *new_area) {
    brute_force_area = new_area;
}

Area3D *OrcBruteForce::get_brute_force_area() {
    return brute_force_area;
}

void OrcBruteForce::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_brute_force_area"), &OrcBruteForce::get_brute_force_area);
    ::ClassDB::bind_method(D_METHOD("set_brute_force_area"), &OrcBruteForce::set_brute_force_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "brute_force_area", PROPERTY_HINT_NODE_TYPE, Area3D::get_class_static()), "set_brute_force_area", "get_brute_force_area");

    ::ClassDB::bind_method(D_METHOD("get_hit_damage"), &OrcBruteForce::get_hit_damage);
    ::ClassDB::bind_method(D_METHOD("set_hit_damage"), &OrcBruteForce::set_hit_damage);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "hit_damage"), "set_hit_damage", "get_hit_damage");

    ::ClassDB::bind_method(D_METHOD("get_brute_force_vfx"), &OrcBruteForce::get_brute_force_vfx);
    ::ClassDB::bind_method(D_METHOD("set_brute_force_vfx"), &OrcBruteForce::set_brute_force_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "brute_force_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_brute_force_vfx", "get_brute_force_vfx");
}

void OrcBruteForce::set_hit_damage(float new_hit_damage) {
    hit_damage = new_hit_damage;
}

float OrcBruteForce::get_hit_damage() {
    return hit_damage;
}

void OrcBruteForce::set_brute_force_vfx(const Ref<PackedScene> &new_brute_force_vfx) {
    brute_force_vfx = new_brute_force_vfx;
}

Ref<PackedScene> OrcBruteForce::get_brute_force_vfx() {
    return brute_force_vfx;
}