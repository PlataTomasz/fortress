#if !defined(PROJECTILE_HPP_INCLUDED)
#define PROJECTILE_HPP_INCLUDED

#include "entity.hpp"

class Projectile : public Entity
{
GDCLASS(Projectile, Entity);

protected:
    static void _bind_methods();
public:
   // void onCollision(const Area3D &collider);

    virtual void _ready();

    Projectile();
    ~Projectile();
};

#endif // PROJECTILE_HPP_INCLUDED
