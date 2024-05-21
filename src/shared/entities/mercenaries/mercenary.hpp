#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include <shared/entities/entity.h>
#include <shared/abilities/ability.hpp>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/helpers/object_ptr.h>

#include <shared/entities/traits/traits.h>
#include <shared/entities/traits/t_uses_abilities.h>
#include <shared/entities/traits/t_has_attributes.h>

class StatusEffectVictimComponent;

/**
 * Mercenary is a class responsible for representing
 * specialization of entity which is primarily supposed
 * to be controlled by Player.
*/
class Mercenary : public Entity, public TUsesAbilities, public THasAttributes
{
GDCLASS(Mercenary, Entity);
protected:
    StatusEffectVictimComponent *status_effect_victim_component = nullptr;

    static void _bind_methods();

    virtual Node *_get_component(const String& component_typename) override;
public:
    StatusEffectVictimComponent *get_status_effect_victim_component();
    void set_status_effect_victim_component(StatusEffectVictimComponent *p_status_effect_vicitm_component);

    Mercenary();

    ~Mercenary();
};

#endif // MERCENARY_HPP_INCLUDED