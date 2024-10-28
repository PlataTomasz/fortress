#include "orc_leap_slam_ability.h"

#include <scene/3d/physics/area_3d.h>

void OrcLeapSlamAbility::set_leap_slam_area(Area3D *new_leap_slam_area) {
    leap_slam_area = new_leap_slam_area;
}

Area3D *OrcLeapSlamAbility::get_leap_slam_area() {
    return leap_slam_area;
}

void OrcLeapSlamAbility::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_leap_slam_area"), &OrcLeapSlamAbility::get_leap_slam_area);
    ClassDB::bind_method(D_METHOD("set_leap_slam_area", "leap_slam_area"), &OrcLeapSlamAbility::set_leap_slam_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "leap_slam_area", PROPERTY_HINT_NODE_TYPE, Area3D::get_class_static()), "set_leap_slam_area", "get_leap_slam_area");

    ClassDB::bind_method(D_METHOD("get_slam_vfx"), &OrcLeapSlamAbility::get_slam_vfx);
    ClassDB::bind_method(D_METHOD("set_slam_vfx", "slam_vfx"), &OrcLeapSlamAbility::set_slam_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "slam_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_slam_vfx", "get_slam_vfx");

    ClassDB::bind_method(D_METHOD("get_slam_hit_vfx"), &OrcLeapSlamAbility::get_slam_hit_vfx);
    ClassDB::bind_method(D_METHOD("set_slam_hit_vfx", "slam_hit_vfx"), &OrcLeapSlamAbility::set_slam_hit_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "slam_hit_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_slam_hit_vfx", "get_slam_hit_vfx");
}

void OrcLeapSlamAbility::set_slam_vfx(const Ref<PackedScene> &new_slam_vfx) {
    slam_vfx = new_slam_vfx;
}

Ref<PackedScene> OrcLeapSlamAbility::get_slam_vfx() {
    return slam_vfx;
}

void OrcLeapSlamAbility::set_slam_hit_vfx(const Ref<PackedScene> &new_slam_hit_vfx) {
    slam_hit_vfx = new_slam_hit_vfx;
}

Ref<PackedScene> OrcLeapSlamAbility::get_slam_hit_vfx() {
    return slam_hit_vfx;
}