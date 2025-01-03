#include "bleeding_status_effect.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/core/managers/component_manager.h>
#include <shared/data_holders/builders/damage_object_builder.h>

#include <scene/main/timer.h>

void BleedingStatusEffect::_on_apply() {
    // Deal damage every 0.5 seconds
    Timer *timer = memnew(Timer);
    timer->set_wait_time(0.5);
    timer->set_autostart(true);
    timer->connect("timeout", callable_mp(this, &BleedingStatusEffect::_on_bleed_tick));
    add_child(timer, true);
}

void BleedingStatusEffect::_on_remove() {

}

void BleedingStatusEffect::set_damage(float p_damage) {
    damage = p_damage;
}

float BleedingStatusEffect::get_damage() {
    return damage;
}


void BleedingStatusEffect::_on_bleed_tick() {
    Entity *ent = get_victim_component()->get_owning_entity();
    ERR_FAIL_NULL(ent);

    DamageableComponent *damageable = ent->get_damageable_component();
    if(!damageable) return;

    damageable->take_damage(
        DamageObjectBuilder()
            .damage_type(DamageObject::DAMAGE_PHYSICAL)
            .damage_subtype_ability()
            .damage_subtype_over_time()
            .value(damage)
            .attacker(get_inflictor())
            .build()
    );
}
