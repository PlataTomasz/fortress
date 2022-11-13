#if !defined(PROJECTILE_HPP_INCLUDED)
#define PROJECTILE_HPP_INCLUDED

#include "entity.hpp"

class Projectile : public Entity
{
GDCLASS(Projectile, Entity);

private:
    float contactDamage = 30.0f;

protected:
    static void _bind_methods(){};
    void movementProcess() override;
public:
    void ready();


    Projectile();
    ~Projectile();
};

#endif // PROJECTILE_HPP_INCLUDED
