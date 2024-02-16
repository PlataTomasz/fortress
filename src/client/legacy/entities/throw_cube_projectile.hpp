#include "projectile.hpp"

class ThrowCubeProjectile : public Projectile
{
GDCLASS(ThrowCubeProjectile, Projectile);
static void _bind_methods(){};

    void ready()
    {
        printf("ThrowCubeProjectile created!");
    };
public:
    ThrowCubeProjectile()
    {
        connect("ready", callable_mp(this, &ThrowCubeProjectile::ready));
    }

    ~ThrowCubeProjectile()
    {

    }
};