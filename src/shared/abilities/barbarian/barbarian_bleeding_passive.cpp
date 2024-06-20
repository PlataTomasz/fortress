#include "barbarian_bleeding_passive.h"

#include <shared/registries/status_effect_registry.h>
#include <shared/core/managers/component_manager.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <server/core/game.h>
#include <shared/status_effects/example/bleeding_status_effect.h>

void BarbarianBleedingPassive::_on_basic_attack_hit(const Ref<DamageObject>& damage_object, Entity *target) {
    Entity *ent = get_ability_caster()->get_owning_entity();
    if(damage_object->get_attacker() == ent) return; // Prevent self damage from applying bleed

    if(!(damage_object->get_subtype() & DamageObject::BASIC_ATTACK_DAMAGE)) return;

    StatusEffectVictimComponent *status_effect_victim = target->get_component<StatusEffectVictimComponent>();
    if(status_effect_victim) {
        BleedingStatusEffect *status_effect = Object::cast_to<BleedingStatusEffect>(Registry<StatusEffect>::get_singleton()->create_instance("barbarian_bleeding_dot"));
        ERR_FAIL_NULL(status_effect);
        // Override damage with proper value
        status_effect->set_damage(5);
        status_effect_victim->apply_status_effect(status_effect);
    }
}

void BarbarianBleedingPassive::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			_ready();
		} break;

		default:
			break;
	}
}

// FIXME: Proper initialization - Ready seems an odd place for it
void BarbarianBleedingPassive::_ready() {
    // Hook to level method
    Entity *ent = get_ability_caster()->get_owning_entity();
    ERR_FAIL_NULL(ent);
    GameLevel *level = ent->get_gamelevel();
    ERR_FAIL_NULL(level);
    level->connect("entity_damage_taken", callable_mp(this, &BarbarianBleedingPassive::_on_basic_attack_hit));
}
