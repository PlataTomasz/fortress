#if !defined(STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED)
#define STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED

#include <shared/entities/components/component.h>
#include <shared/helpers/object_ptr.h>
#include <shared/status_effects/status_effect.hpp>

//Class representing target of status effects
class StatusEffectVictimComponent : public Component
{
GDCLASS(StatusEffectVictimComponent, Component);
public:
    //NOTE: Error codes would be better in this case
    //Remove status effect from entity if it have it: Return true on success, false on fail
    bool remove_status_effect(StringName status_effect_name);
    //NOTE: Maybe I should pass node which owns components rather than the component itself?
    void apply_status_effect_instance(ObjectPtr<StatusEffectInstance> instance);

    //Return status effect pointer if entity have it - nullptr otherwise
    ObjectPtr<StatusEffect> get_status_effect(StringName status_effect_name);
    bool has_status_effect(StringName status_effect_name);
    
    ObjectPtr<StatusEffectInstance> get_status_effect_instance(StringName effect_name);

    //TODO: Implement a way to get all the status effects, so UI can iterate over it
};

#endif // STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED
