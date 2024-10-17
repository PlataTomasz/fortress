#include "barbarian_intimidating_cry_ability.h"

#include <scene/3d/physics/area_3d.h>

void BarbarianIntimidatingCryAbility::set_warcry_area(Area3D *new_warcry_area) {
    warcry_area = new_warcry_area;
}

Area3D *BarbarianIntimidatingCryAbility::get_warcry_area() {
    return warcry_area;
}

void BarbarianIntimidatingCryAbility::set_warcry_vfx(const Ref<PackedScene> &new_vfx) {
    warcry_vfx = new_vfx;
}

Ref<PackedScene> BarbarianIntimidatingCryAbility::get_warcry_vfx() {
    return warcry_vfx;
}

void BarbarianIntimidatingCryAbility::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_warcry_area"), &BarbarianIntimidatingCryAbility::get_warcry_area);
    ::ClassDB::bind_method(D_METHOD("set_warcry_area"), &BarbarianIntimidatingCryAbility::set_warcry_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "warcry_area", PROPERTY_HINT_NODE_TYPE, Area3D::get_class_static()), "set_warcry_area", "get_warcry_area");

    ::ClassDB::bind_method(D_METHOD("get_warcry_vfx"), &BarbarianIntimidatingCryAbility::get_warcry_vfx);
    ::ClassDB::bind_method(D_METHOD("set_warcry_vfx"), &BarbarianIntimidatingCryAbility::set_warcry_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "warcry_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_warcry_vfx", "get_warcry_vfx");
}