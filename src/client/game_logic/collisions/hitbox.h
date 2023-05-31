#if !defined(HITBOX_H_INCLUDED)
#define HITBOX_H_INCLUDED

#include <core/object/object.h>

class Area3D;
class CollisionShape3D;
class SphereShape3D;
class Entity;



/**
 * Abstraction layer for collision handling
*/
class Hitbox : public Area3D
{
GDCLASS(Hitbox, Area3D);
    enum CollisionMask
    {
        NOTHING = 0,
        TERRAIN = 1,
        MINIONS = 1<<1,
        PETS = 1<<2,
        MERCENARIES = 1<<3,
        MONSTERS = 1<<4,
    

        EVERYTHING = 65536
    };

    struct ShapePresets
    {
        static SphereShape3D SPHERE;

    };

private:
    /**
     * Area3D objects that should be ignored for collision checks
    */
    Vector<Area3D*> blacklist;

    bool is_in_blacklist(Area3D* area);
protected:
public:
    void add_collision_shape(CollisionShape3D* collision_shape);
    void remove_collision_shape(CollisionShape3D* collision_shape);
    Vector<Entity*> get_colliding_entities();
    Entity* get_closest_colliding_entity();

    Hitbox();
};

#endif // HITBOX_H_INCLUDED
