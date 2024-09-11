#if !defined(DAMAGEABLE_COMPONENT_INCLUDED)
#define DAMAGEABLE_COMPONENT_INCLUDED

#include <scene/main/node.h>
#include <shared/data_holders/damage_object.hpp>

class DamageableComponent : public Node
{
GDCLASS(DamageableComponent, Node);
private:
    void _on_something_took_damage(const Ref<DamageObject>& something_damage_object);
    void _on_something_took_fatal_damage(const Ref<DamageObject>& something_damage_object);
protected:
    static void _bind_methods();
public:
    Entity *get_owning_entity();
    void take_damage(Ref<DamageObject> damage_object);
    void heal(float value);
    bool is_damageable_by(Ref<DamageObject> damage_object);
};

#endif // DAMAGEABLE_COMPONENT_INCLUDED

