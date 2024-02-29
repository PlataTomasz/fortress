#include "turret.h"

#include <scene/3d/area_3d.h>

void Turret::_on_area_enter_radius(Area3D *area) {
    /*
        When entity's hitbox enters turret range, It gets attacked once per 0.7s.
    */

    Entity *ent = Object::cast_to<Entity>(area->get_parent());
    if (!ent) return; // Not a valid target

    
    // Enable turret
    // turret_active = true;
}

void Turret::_init() {
    detection_area = static_cast<Area3D *>(get_node(NodePath("DetectionArea")));
}