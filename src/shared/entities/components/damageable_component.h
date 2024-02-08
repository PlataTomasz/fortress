#if !defined(DAMAGEABLE_COMPONENT_INCLUDED)
#define DAMAGEABLE_COMPONENT_INCLUDED

#include <scene/main/node.h>
#include <shared/data_holders/damage_object.hpp>

class DamageableComponent : public Node
{
private:

protected:
    void _notification(int notification);
public:
    void take_damage(Ref<DamageObject> damage_object);
};

#endif // DAMAGEABLE_COMPONENT_INCLUDED

