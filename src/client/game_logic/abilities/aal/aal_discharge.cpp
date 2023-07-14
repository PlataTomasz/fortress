#include <client/game_logic/abilities/aal/aal_discharge.hpp>
#include <client/status_effects/status_effect_manager.hpp>
#include <client/string_names/game_string_names.h>

//FIXME: Compiler error because DamageObject doesn't extend Object class. Look for workaround, alternative storage or just extend Object class.
void AalDischarge::on_entity_take_damage(Entity *ent, Dictionary damage_data)
{
    DamageObject damage_object(damage_data);
    ERR_FAIL_COND(!damage_object.is_valid());

    //Checking if we inflicted damage
    if(owner == damage_object.inflictor)
    {
        StatusEffect* status_effect = ent->get_status_effect("aal_discharge");

        if(status_effect == nullptr)
        {
            //Deal damage if attempt to apply more than maximum stacks and purge them
            if(status_effect->get_current_stacks() < 3)
            {
                status_effect->add_stacks();
            }
            else
            {
                ent->take_damage({
                    DamageType::DAMAGE_MAGICAL,
                    //TODO: Level and XP API
                    //get_base_damage() + get_damage_per_level()*owner->get_level(),
                    get_base_damage(),
                    this->owner.get()
                });
                ent->remove_status_effect(status_effect);
            }
        }
        else
        {
            status_effect = new StatusEffect("aal_discharge");
            ent->apply_status_effect("aal_discharge", 2.5, this->owner.get());
        }
    }
    
}

void AalDischarge::set_owner_callback()
{
    //TODO: Entity class should extend INotificator
}

void AalDischarge::ready_impl()
{
    
}