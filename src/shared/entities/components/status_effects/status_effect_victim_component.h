#if !defined(STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED)
#define STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED

#include <shared/entities/components/component.h>
#include <shared/helpers/object_ptr.h>
#include <shared/status_effects/status_effect.hpp>

//Class representing target of status effects
class StatusEffectVictimComponent : public Component
{
GDCLASS(StatusEffectVictimComponent, Component);
protected:
    static void _bind_methods();
public:
    //NOTE: Error codes would be better in this case
    //Remove status effect from entity if it have it: Return true on success, false on fail
    bool remove_status_effect(StringName status_effect_name);

    //Return status effect pointer if entity have it - nullptr otherwise
    StatusEffect *get_status_effect(StringName status_effect_name);
    bool has_status_effect(StringName status_effect_name);

    bool apply_status_effect(const StringName &status_effect_name);
    bool apply_status_effect(StatusEffect *status_effect);

    //TODO: Implement a way to get all the status effects, so UI can iterate over it
};

#endif // STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED
