#include "barbarian_bleeding_passive.h"

#include <shared/registries/status_effect_registry.h>
#include <shared/core/managers/component_manager.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <server/core/game.h>

void BarbarianBleedingPassive::_on_basic_attack_hit(Entity *target, AbilityCasterComponent *inflictor, void *caused_by) {
    StatusEffect *status_effect = Registry<StatusEffect>::get_singleton()->create_instance("barbarian_bleeding_dot");
    // Override damage with proper value
    status_effect->set("damage", 5);
    
    StatusEffectVictimComponent *status_effect_victim = target->get_component<StatusEffectVictimComponent>();
    if(status_effect_victim) {
        status_effect_victim->apply_status_effect(status_effect);
    }
}

void BarbarianBleedingPassive::_init() {
    // Setup callbacks
    //Realm::get_game()->connect("basic_attack_hit", callable_mp(this, &BarbarianBleedingPassive::_on_basic_attack_hit));
}