#include <client/game_logic/collisions/hitbox.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/3d/area_3d.h>
#include <scene/3d/ray_cast_3d.h>

Hitbox::Hitbox()
{

}

void Hitbox::add_collision_shape(CollisionShape3D* collision_shape)
{
    add_child(collision_shape);
}

void Hitbox::remove_collision_shape(CollisionShape3D* collision_shape)
{
    remove_child(collision_shape);
}

Vector<Entity*> Hitbox::get_colliding_entities()
{
    TypedArray<Area3D> colliding_areas = get_overlapping_areas();
    Vector<Entity*> entities;
    entities.resize(colliding_areas.size());

    for(int i = 0;i<colliding_areas.size();i++)
    {
        Area3D* collider = (Area3D*)&*(colliding_areas[i]);

        //Prevent non-entities from being included
        if(Entity* ent = Object::cast_to<Entity>(collider->get_parent()))
        {
            entities.append(ent);
        }
    }

    return entities;
}

Entity* Hitbox::get_closest_colliding_entity()
{
    TypedArray<Area3D> colliding_areas = get_overlapping_areas();

    RayCast3D* raycast = memnew(RayCast3D);
    raycast->set_collide_with_areas(true);
    raycast->set_global_position(this->get_global_position());

    Entity* closest_entity = nullptr;
    double closest_distance = 0;

    for(int i = 0;i<colliding_areas.size();i++)
    {
        Area3D* collider = (Area3D*)&*(colliding_areas[i]);

        if(Entity* ent = Object::cast_to<Entity>(collider->get_parent()))
        {
            raycast->set_target_position(this->get_global_position() - collider->get_global_position());
            //TODO: Check what collider gets picked there are more than one with equal sizes and distance
            Area3D* raycast_collider = (Area3D*)raycast->get_collider();
            Vector3 collision_point = raycast->get_collision_point();

            if(raycast_collider && raycast_collider == collider && !is_in_blacklist(collider))
            {
                double new_closest_distance = collision_point.distance_squared_to(Vector3());
                if(new_closest_distance < closest_distance || closest_entity)
                {
                    if(Entity* ent = Object::cast_to<Entity>(collider->get_parent()))
                    {
                        closest_distance = new_closest_distance;
                        closest_entity = ent;
                    }
                }
            }
        }
    }


    return closest_entity;
}

bool Hitbox::is_in_blacklist(Area3D* area)
{
    for(Area3D* blacklist_elem : blacklist)
    {
        if(blacklist_elem == area)
        {
            return true;
        }
    }
    return false;
}