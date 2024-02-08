#include "status_effect_victim_component.h"
#include <shared/status_effects/status_effect_instance.h>

StatusEffectVictimComponent::StatusEffectVictimComponent()
{

}
//TODO: Implement
bool StatusEffectVictimComponent::remove_status_effect(StringName status_effect_name)
{
    return true;
}
//TODO: Implement
ObjectPtr<StatusEffectInstance> StatusEffectVictimComponent::get_status_effect_instance(StringName effect_name)
{
    return ObjectPtr<StatusEffectInstance>();
}

void StatusEffectVictimComponent::apply_status_effect_instance(ObjectPtr<StatusEffectInstance> instance)
{
    add_child(instance);
}