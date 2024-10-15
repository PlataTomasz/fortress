#include "orc_crushing_blows_buff.h"

#include <shared/core/game_level.h>
#include <shared/entities/entity.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>

#include <shared/registries/status_effect_registry.h>

void OrcCrushingBlowsBuff::_on_apply() {
    // Listen to event, whenever an entity is hit with a basic attack by orc
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_gamelevel());
	get_victim_entity()->get_gamelevel()->connect("entity_damage_taken", callable_mp(this, &OrcCrushingBlowsBuff::_on_basic_attack_damage_dealt));
}

void OrcCrushingBlowsBuff::_on_remove() {
    // Listen to event, whenever an entity is hit with a basic attack by orc
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_gamelevel());
	get_victim_entity()->get_gamelevel()->disconnect("entity_damage_taken", callable_mp(this, &OrcCrushingBlowsBuff::_on_basic_attack_damage_dealt));
}

void OrcCrushingBlowsBuff::_on_basic_attack_damage_dealt(const Ref<DamageObject> damage_object, Entity *target) {
	if(!(damage_object->get_subtype() & DamageObject::BASIC_ATTACK_DAMAGE)) return;

    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_gamelevel());

	if (damage_object->get_attacker() != get_victim_entity()) return;

    // Ensure that attacker and target are not allies
    
    ERR_FAIL_NULL(target);

	StatusEffectVictimComponent *status_effect_component = target->get_status_effect_victim_component();
    ERR_FAIL_NULL(status_effect_component);

    StatusEffect *status_effect = StatusEffectRegistry::get_singleton()->create_instance("orc_crushing_blows_debuff");
    ERR_FAIL_NULL(status_effect);

	status_effect_component->apply_status_effect(status_effect);
    this->expire();
}