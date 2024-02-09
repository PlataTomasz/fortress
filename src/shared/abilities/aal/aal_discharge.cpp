#include <shared/abilities/aal/aal_discharge.hpp>
#include <shared/status_effects/status_effect_manager.hpp>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/status_effects/status_effect_instance.h>

#include <shared/string_names/component_stringnames.h>
#include <shared/string_names/signal_stringnames.h>

void AalDischarge::on_entity_take_damage(Entity *ent, Ref<DamageObject> damage_object)
{
    //TODO: Use Object Metadata
    ObjectPtr<StatusEffectVictimComponent> status_effect_victim = ent->get_component<StatusEffectVictimComponent>(ComponentStringNames::get_singleton()->STATUS_EFFECT_VICTIM);
    ObjectPtr<DamageableComponent> damageable_target = ent->get_component<DamageableComponent>(ComponentStringNames::get_singleton()->DAMAGEABLE);

    //Checking if we inflicted damage
    if(owner == damage_object->inflictor)
    {
        ObjectPtr<StatusEffectInstance> status_effect = status_effect_victim->get_status_effect_instance("aal_discharge");

        if(!status_effect.is_valid())
        {
            //Deal damage if attempt to apply more than maximum stacks and purge them
            if(status_effect->get_current_stacks() < 3)
            {
                status_effect->add_stacks(1, true);
            }
            else
            {
                DamageObject *take_damage_object = memnew(DamageObject(
                    DamageObject::DamageType::DAMAGE_MAGICAL,
                    //TODO: Level and XP API
                    //get_base_damage() + get_damage_per_level()*owner->get_level(),
                    20,
                    this->owner
                ));

                damageable_target->take_damage(take_damage_object);
                status_effect_victim->remove_status_effect("aal_discharge");
            }
        }
        else
        {
            status_effect = StatusEffectManager::get_singleton()->create_status_effect_instance("aal_discharge");
            status_effect_victim->apply_status_effect_instance(status_effect);
        }
    }
    
}

void AalDischarge::set_owner_callback()
{
    if(old_owner)
    {
        disconnect(SignalStringNames::get_singleton()->ON_DAMAGE_TAKEN, callable_mp(this, &AalDischarge::on_entity_take_damage));
    }

    owner->connect(SignalStringNames::get_singleton()->ON_DAMAGE_TAKEN, callable_mp(this, &AalDischarge::on_entity_take_damage));
}

void AalDischarge::ready_impl()
{
    
}