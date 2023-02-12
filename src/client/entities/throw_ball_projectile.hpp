#include "projectile.hpp"

#include <classes/engine.hpp>

class ThrowBallProjectile : public Projectile
{
GDCLASS(ThrowBallProjectile, Projectile);
static void _bind_methods(){};

    void ready()
    {
        //TODO: Is not a ball, but a cube.
        printf("ThrowBallProjectile created!");
    };
public:
    ThrowBallProjectile()
    {

    }

    ~ThrowBallProjectile()
    {

    }
};