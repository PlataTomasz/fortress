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
public:
    void take_damage(Ref<DamageObject> damage_object);

    /**
     * value - amount of damage to be inflictedg
     * inflictor - who caused the damage? Monster, minion, mercenary, etc.
     * caused_by - what was direct cause of inflicting damage? Basic attack, ability, enviroment, etc.
    */
    void take_damage(float value, Node *inflictor, Node *caused_by);
    void heal(float value);
};

#endif // DAMAGEABLE_COMPONENT_INCLUDED

