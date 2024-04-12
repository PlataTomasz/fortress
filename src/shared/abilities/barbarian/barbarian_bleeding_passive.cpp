#include "barbarian_bleeding_passive.h"

#include <shared/status_effects/status_effect_factory.h>
#include <shared/core/managers/component_manager.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <server/core/game.h>

void BarbarianBleedingPassive::_on_basic_attack_hit(Entity *target, AbilityCasterComponent *inflictor, void *caused_by) {
    StatusEffect *status_effect = StatusEffectFactory::create_status_effect("barbarian_bleeding_dot");
    // Override damage with proper value
    status_effect->set("damage", 5);
    
    StatusEffectVictimComponent *status_effect_victim = ComponentManager::get_component<StatusEffectVictimComponent>(target);
    status_effect_victim->apply_status_effect(status_effect);
}

void BarbarianBleedingPassive::_init() {
    // Setup callbacks
    Realm::get_game()->connect("basic_attack_hit", callable_mp(this, &BarbarianBleedingPassive::_on_basic_attack_hit));
}