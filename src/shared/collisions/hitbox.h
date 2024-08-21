#if !defined(HITBOX_H_INCLUDED)
#define HITBOX_H_INCLUDED

#include <core/object/object.h>
#include <scene/3d/physics/area_3d.h>

class CollisionShape3D;
class SphereShape3D;
class Entity;

#include <shared/helpers/object_ptr.h>

/**
 * Hitbox class is an Extension of Area3D class, which implements a better way of obtaining other Area3D object, that overlap with that object.
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
private:
    /**
     * Area3D objects that should be ignored for collision checks
    */
    Vector<Area3D*> blacklist;

    bool is_in_blacklist(Area3D* area);
protected:
public:
    Hitbox();
};

#endif // HITBOX_H_INCLUDED
