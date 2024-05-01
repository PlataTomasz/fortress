#include "orc_brute_force.h"

#include <scene/3d/area_3d.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/box_shape_3d.h>

void OrcBruteForce::_use(const Ref<ActionContext> &action_context) {
    // Facade?
    Area3D *area_3d = memnew(Area3D);
    CollisionShape3D *collision_shape_3d = memnew(CollisionShape3D);
    Shape3D *shape_3d = memnew(BoxShape3D);

    
}