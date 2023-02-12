#include "projectile.hpp"

class ThrowCubeProjectile : public Projectile
{
GDCLASS(ThrowCubeProjectile, Projectile);
static void _bind_methods(){};

    void _ready() override
    {
        printf("ThrowCubeProjectile created!");
    };
public:
    ThrowCubeProjectile()
    {

    }

    ~ThrowCubeProjectile()
    {

    }
};