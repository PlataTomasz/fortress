#include "hitbox_component.h"

#include <shared/helper_macros.h>

#include <scene/3d/area_3d.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/cylinder_shape_3d.h>

void HitboxComponent::_init() {
    DISABLE_IN_EDITOR();
    area = memnew(Area3D);
    add_child(area);

    collision_shape = memnew(CollisionShape3D);
    add_child(collision_shape);

    CylinderShape3D *shape = memnew(CylinderShape3D);
    collision_shape->set_shape(shape);
}

