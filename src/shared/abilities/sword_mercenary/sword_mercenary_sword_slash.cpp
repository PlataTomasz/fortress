#include "sword_mercenary_sword_slash.h"
#include <scene/2d/area_2d.h>
#include <scene/2d/collision_shape_2d.h>
#include <scene/resources/circle_shape_2d.h>

void SwordMercenarySwordSlash::use_impl(UseContext& use_context)
{
    //Slash sword in a circle dealing physical damage
    /*
    Area3D *area = memnew(Area3D);
    CollisionShape3D *coll_shape = memnew(CollisionShape2D);
    CircleShape3D *shape = memnew(CircleShape2D);

    coll_shape->set_shape(shape);
    //TODO: Collision detection

    TypedArray<Area3D> colliders = area->get_overlapping_areas();

    for(int i = 0;i < colliders.size();i++)
    {
        Area3D *collider = (Area3D*)(colliders[i].operator Object *());

        //TODO: Check for entity
        collider->get_parent();
    }
    */
}