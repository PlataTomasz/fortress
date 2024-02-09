#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include <shared/entities/entity.h>
#include <shared/abilities/ability.hpp>
#include <shared/entities/components/abilities/ability_caster_component.h>

/**
 * Mercenary is a class responsible for representing
 * specialization of entity which is primarily supposed
 * to be controlled by Player.
*/
class Mercenary : public Entity
{
GDCLASS(Mercenary, Entity);
protected:
    static void _bind_methods();
public:
    void _notification(int notification);

    void initialize();
    void tick();

    Mercenary();

    ~Mercenary();
};

#endif // MERCENARY_HPP_INCLUDED