#if !defined(HITBOX_H_INCLUDED)
#define HITBOX_H_INCLUDED

#include <core/object/object.h>

class Area3D;
class CollisionShape3D;
class SphereShape3D;
class Entity;

#include <shared/helpers/object_ptr.h>

/**
 * Interface 
*/
class Hitbox
{
    enum CollisionMask : uint32_t
    {
        NOTHING = 0,
        TERRAIN = 1,
        MINIONS = 1<<1,
        PETS = 1<<2,
        MERCENARIES = 1<<3,
        MONSTERS = 1<<4,
    

        //Godot stores collision mask in uint32_t - Check CollisionObject3D
        EVERYTHING = UINT32_MAX
    };

    //Area which is managed by that Hitbox instance
    ObjectPtr<Area3D> area = ObjectPtr(memnew(Area3D));

    //Offset of hitbox
    Vector3 offset;

private:
    /**
     * Area3D objects that should be ignored for collision checks
    */
    Vector<Area3D*> blacklist;

    void set_collision_mask(CollisionMask collision_mask);
    uint32_t get_collision_mask();

    bool is_in_blacklist(Area3D* area);
protected:
public:
    void add_collision_shape(CollisionShape3D* collision_shape);
    void remove_collision_shape(CollisionShape3D* collision_shape);
    Vector<Entity*> get_colliding_entities();
    virtual Entity* get_closest_colliding_entity();

    //Hitbox object offset
    void set_offset(const Vector3& offset);
    const Vector3& get_offset();

    Hitbox();
};

#endif // HITBOX_H_INCLUDED
