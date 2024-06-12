#if !defined(DAMAGEABLE_COMPONENT_INCLUDED)
#define DAMAGEABLE_COMPONENT_INCLUDED

#include <scene/main/node.h>
#include <shared/data_holders/damage_object.hpp>

template<class T>
class ObjectPtr;

class DamageableComponent : public Node
{
GDCLASS(DamageableComponent, Node);
protected:
    static void _bind_methods();
public:
    Entity *get_owning_entity();
    void take_damage(Ref<DamageObject> damage_object);
    void heal(float value);
};

#endif // DAMAGEABLE_COMPONENT_INCLUDED

