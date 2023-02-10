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
        if(!Engine::get_singleton()->is_editor_hint())
        {
            //TODO: Find alternative for callable_mp
            //connect("ready", callable_mp(this, &ThrowBallProjectile::ready));
        }
    }

    ~ThrowBallProjectile()
    {

    }
};