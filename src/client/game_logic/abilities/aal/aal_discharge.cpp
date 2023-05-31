#include <client/game_logic/abilities/aal/aal_discharge.hpp>
#include <client/status_effects/status_effect_manager.hpp>

void AalAboveDecree::on_entity_take_damage(Entity* ent, DamageObject damageObject)
{
    //Checking if we inflicted damage
    if(damageObject.inflictor == owner)
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
                    40,
                    this->owner
                });
                ent->remove_status_effect(status_effect);
            }
        }
        else
        {
            status_effect = new StatusEffect("aal_discharge");
        }
    }
}