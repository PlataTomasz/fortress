#include "bleeding_status_effect.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <shared/core/managers/component_manager.h>


void BleedingStatusEffect::_on_apply() { 
    //damageable_component = ComponentManager::get_component<DamageableComponent>(get_victim_component());
    /*
        value - how much damage is dealt?
        type - what type of damage is this?
        inflictor - who inflicted damage
        caused_by - the direct cause of the damage, ex. basic attack, ability
    */
    //damageable_component->take_damage(value, type, subtype, inflictor, caused_by);
}
