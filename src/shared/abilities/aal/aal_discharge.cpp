#include <shared/abilities/aal/aal_discharge.hpp>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/status_effects/status_effect.hpp>

#include <shared/string_names/component_stringnames.h>
#include <shared/string_names/signal_stringnames.h>

void AalDischarge::on_entity_take_damage(Entity *ent, Ref<DamageObject> damage_object)
{
    //TODO: Use Object Metadata
    ObjectPtr<StatusEffectVictimComponent> status_effect_victim = ent->get_component<StatusEffectVictimComponent>();
    ObjectPtr<DamageableComponent> damageable_target = ent->get_component<DamageableComponent>();

    //Checking if we inflicted damage
    if(get_owner() == damage_object->inflictor)
    {
        StatusEffect *status_effect = status_effect_victim->get_status_effect("aal_discharge");

        if(!status_effect)
        {
            //Deal damage if attempt to apply more than maximum stacks and purge them
            if(status_effect->get_current_stacks() < 3)
            {
                status_effect->add_stacks(1, true);
            }
            else
            {
                damageable_target->take_damage(20, this->get_owner(), this);
                status_effect_victim->remove_status_effect("aal_discharge");
            }
        }
        else
        {
            status_effect_victim->apply_status_effect("aal_discharge");
        }
    }
    
}

void AalDischarge::set_owner_callback()
{
    get_owner()->connect(SignalStringNames::get_singleton()->ON_DAMAGE_TAKEN, callable_mp(this, &AalDischarge::on_entity_take_damage));
}

void AalDischarge::ready_impl()
{
    
}