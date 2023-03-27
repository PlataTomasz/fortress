#include "fist_mercenary_basic_attack.hpp"
#include <scene/3d/collision_shape_3d.h>
#include <scene/3d/ray_cast_3d.h>
#include <scene/resources/primitive_meshes.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>
#include <scene/resources/box_shape_3d.h>

void FistMercenaryBasicAttackAbility::use_impl(UseContext use_context)
{
    Entity* user = use_context.get_user();

    RayCast3D* raycast = memnew(RayCast3D);
    raycast->set_position(user->get_position());
    raycast->add_exception(hitbox);
    raycast->add_exception(user->hitbox);
    raycast->set_collide_with_areas(true);
    
    TypedArray<Area3D> colliders = hitbox->get_overlapping_areas();

    Area3D* closest_collider = nullptr;
    double shortest_distance = 0; 

    print_line("Size of colliders: ", colliders.size());

    for(int i = 0;i < colliders.size();i++)
    {
        Area3D* collider = (Area3D*)&*(colliders[i]);

        print_line("Current collider: ", collider);

        raycast->set_target_position(collider->get_position());

        Vector3 collision_point = raycast->get_collision_point();
        double distance = Math::abs(raycast->get_target_position().distance_squared_to(collision_point));
        if(distance < shortest_distance || closest_collider == nullptr)
        {
            shortest_distance = distance;
            closest_collider = collider;
        }

    }

    //No colliders
    if(closest_collider == nullptr) return;

    print_line("Closest collider: ", closest_collider);
    print_line("Parent: ", closest_collider->get_parent());

    //NOTE: We assume that hitbox is direct child of Entity node
    Entity* ent = (Entity*)closest_collider->get_parent();

    ent->take_damage({
        DAMAGE_PHYSICAL,
        50,
        this->owner
    });
}

void FistMercenaryBasicAttackAbility::initialize()
{
    double hitbox_width = 0.1;
    double hitbox_length = 0.3;

    hitbox = memnew(Area3D);
    hitbox->set_name("BasicAttackHitbox");

    CollisionShape3D* collision_shape = memnew(CollisionShape3D);
    BoxShape3D* shape = memnew(BoxShape3D);
    //10 is just random number - not important
    shape->set_size(Vector3(hitbox_width, 10, hitbox_length));

    collision_shape->set_shape(shape);

    hitbox->add_child(collision_shape);
    owner->add_child(hitbox);

    double x = 0.3; 
    //TODO: Offset hitbox 
    hitbox->set_position(Vector3(x, 0, 0));
    hitbox->set_rotation(owner->get_global_rotation());
}

FistMercenaryBasicAttackAbility::FistMercenaryBasicAttackAbility(Entity* owner) : BasicAttackAbility(owner)
{

}