#include "dance_with_death_status.h"

#include <scene/main/timer.h>

#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/entity.h>
#include <shared/core/game_level.h>

void DanceWithDeathStatus::_on_apply() {
	// Take damage every second
	// TODO: Probably a better approach would be to separate damage over time code and configure from editor
	Timer *timer = memnew(Timer);
	timer->set_wait_time(0.5); // Trigger every 0.5s
	timer->set_autostart(true);
	timer->connect("timeout", callable_mp(this, &DanceWithDeathStatus::_on_self_damage_tick));
	add_child(timer);

	// Hook into level/game to know when entity on level was hit by owner attack

	// Entity "x", was hit with "y" by "z" on level "w"
	/*
	So:
	- Entity: on_hit(with, by) - I've been hit!
	- Level: on_entity_hit(entity, with, by) - Something has been hit!
	- Game: on_level_entity_hit(entity, with, by, on_level) - Something has been hit on certain GameLevel
	*/

	Entity *ent = get_victim_component()->get_owning_entity();
	GameLevel *level = ent->get_gamelevel();
	level->connect("entity_damage_taken", callable_mp(this, &DanceWithDeathStatus::_on_basic_attack_damage_dealt));
}

void DanceWithDeathStatus::_on_self_damage_tick() {
	Entity *ent = get_victim_component()->get_owning_entity();
	DamageableComponent *damageable = ent->get_component<DamageableComponent>();
	if (damageable) {
		damageable->take_damage(memnew(DamageObject(DamageObject::DAMAGE_PHYSICAL, (DamageObject::OVER_TIME_DAMAGE | DamageObject::SELF_DAMAGE), 5, ent))); 
	}
}

// Heal when owner's attack hits
void DanceWithDeathStatus::_on_basic_attack_damage_dealt(const Ref<DamageObject> damage_object, Entity *target) { // TODO: Figure out how should with be passed(Wrapper object or interface?)
	// Only heal on basic attack hit
	if(!(damage_object->get_subtype() & DamageObject::BASIC_ATTACK_DAMAGE)) return;

	Entity *ent = get_victim_component()->get_owning_entity();
	if (damage_object->get_attacker() != ent) return;

	DamageableComponent *damageable = ent->get_component<DamageableComponent>();
	if (damageable) {
		damageable->heal(8);
	}
}

void DanceWithDeathStatus::_on_remove() {
}
