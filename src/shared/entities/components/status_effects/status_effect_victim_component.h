#if !defined(STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED)
#define STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED

#include <shared/entities/components/component.h>
#include <shared/helpers/object_ptr.h>
#include <shared/status_effects/status_effect.hpp>
#include <shared/data_holders/damage_object.hpp>

//Class representing target of status effects
class StatusEffectVictimComponent : public Component
{
GDCLASS(StatusEffectVictimComponent, Component);
private:
    void _on_child_added(Node *p_child);
    void _on_child_removed(Node *p_child);
    void _on_death(const Ref<DamageObject> &damage_object);
protected:
    static void _bind_methods();
    void _notification(int p_notification);
public:
    void clear();

    bool already_has_other_instance(StatusEffect *status_effect);

    //NOTE: Error codes would be better in this case
    //Remove status effect from entity if it have it: Return true on success, false on fail
    bool remove_status_effect(StringName status_effect_name);

    //Return status effect pointer if entity have it - nullptr otherwise
    StatusEffect *get_status_effect(StringName status_effect_name);
    bool has_status_effect(StringName status_effect_name);

    bool apply_status_effect(const StringName &status_effect_name);
    bool apply_status_effect(StatusEffect *status_effect);

    bool can_effect_be_applied(StatusEffect *status_effect);

    Entity *get_owning_entity();

    // Returns all the status effects associated with this component
    List<StatusEffect *> get_status_effects();

    //TODO: Implement a way to get all the status effects, so UI can iterate over it
};

#endif // STATUS_EFFECT_INFLICTOR_COMPONENT_INCLUDED
