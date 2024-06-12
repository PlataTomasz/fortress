#include <shared/abilities/aal/aal_discharge.hpp>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/status_effects/status_effect.hpp>

#include <shared/string_names/component_stringnames.h>
#include <shared/string_names/signal_stringnames.h>
#include <shared/entities/components/abilities/ability_caster_component.h>

void AalDischarge::on_entity_take_damage(Entity *ent, Ref<DamageObject> damage_object)
{
    //TODO: Use Object Metadata
    ObjectPtr<StatusEffectVictimComponent> status_effect_victim = ent->get_component<StatusEffectVictimComponent>();
    ObjectPtr<DamageableComponent> damageable_target = ent->get_component<DamageableComponent>();

    //Checking if we inflicted damage
    if(get_owner() == damage_object->attacker)
    {
        StatusEffect *status_effect = status_effect_victim->get_status_effect("aal_discharge");

        if(!status_effect)
        {
            //Deal damage if attempt to apply more than maximum stacks and purge them
            if(status_effect->get_current_stacks() < 3)
            {
                //status_effect->add_stacks(1, true);
                status_effect->add_stacks();
            }
            else
            {
                damageable_target->take_damage(memnew(DamageObject(DamageObject::DAMAGE_MAGICAL, DamageObject::ABILITY_DAMAGE & DamageObject::AREA_DAMAGE, 15, get_ability_caster()->get_owning_entity())));
                status_effect_victim->remove_status_effect("aal_discharge");
            }
        }
        else
        {
            status_effect_victim->apply_status_effect("aal_discharge");
        }
    }
    
}

void AalDischarge::_ready()
{
    
}