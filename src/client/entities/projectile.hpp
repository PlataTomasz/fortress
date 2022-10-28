#if !defined(PROJECTILE_HPP_INCLUDED)
#define PROJECTILE_HPP_INCLUDED

#include "entity.hpp"

class Projectile : public Entity
{
GDCLASS(Projectile, Entity);

protected:
    static void _bind_methods(){};
public:
    Projectile();
    ~Projectile();
};

#endif // PROJECTILE_HPP_INCLUDED
