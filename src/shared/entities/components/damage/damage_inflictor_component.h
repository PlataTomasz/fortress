#if !defined(AI_COMPONENT_INCLUDED)
#define AI_COMPONENT_INCLUDED

#include "../component.h"
#include <shared/data_holders/damage_object.hpp>

class DamageableComponent;

/**
 * Component that describes object that deals damage to others
*/
class DamageInflictorComponent : public Component
{
private:

protected:
    
public:
    //FIXME: Currently unimplemented methods
    void deal_damage(DamageableComponent *target, Ref<DamageObject> damage_object){};
    //Returns name of entity, which is parent of that component
    void get_entity_name(){};
};

#endif // AI_COMPONENT_INCLUDED
