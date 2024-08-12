#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include <shared/entities/entity.h>
#include <shared/abilities/ability.hpp>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/helpers/object_ptr.h>

class StatusEffectVictimComponent;

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

    virtual Node *_get_component(const String& component_typename) override;

    Ref<Texture2D> portrait_icon;
public:
    Ref<Texture2D> get_portrait_icon();
    void set_portrait_icon(const Ref<Texture2D>& p_icon);

    Mercenary();

    ~Mercenary();
};

#endif // MERCENARY_HPP_INCLUDED