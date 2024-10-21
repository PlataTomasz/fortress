#include "barbarian_barbaric_might_buff.h"

#include <shared/entities/entity.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/data_holders/builders/damage_object_builder.h>
#include <shared/core/game_level.h>
#include <shared/core/sh_game.h>

void BarbarianBarbaricMightBuff::_on_apply() {
    Entity *ent = get_victim_entity();
    ERR_FAIL_NULL(ent);

	GameLevel *level = ent->get_gamelevel();
    ERR_FAIL_NULL(level);
    level->connect("entity_damage_taken", callable_mp(this, &BarbarianBarbaricMightBuff::_on_basic_attack_damage));
}

void BarbarianBarbaricMightBuff::_on_remove() {
    Entity *ent = get_victim_entity();
    ERR_FAIL_NULL(ent);

	GameLevel *level = ent->get_gamelevel();
    ERR_FAIL_NULL(level);
    level->disconnect("entity_damage_taken", callable_mp(this, &BarbarianBarbaricMightBuff::_on_basic_attack_damage));
}

void BarbarianBarbaricMightBuff::_on_basic_attack_damage(const Ref<DamageObject> damage_object, Entity *target) {
    ERR_FAIL_NULL(target);

    if(!damage_object->is_basic_attack_damage()) return;
    if(damage_object->get_attacker() != get_victim_entity()) return;
    
    DamageableComponent *damageable = target->get_damageable_component();
    if(damageable) {
        damageable->take_damage(
            DamageObjectBuilder()
                .damage_type(DamageObject::DAMAGE_PHYSICAL)
                .damage_subtype_ability()
                .value(3)
                .attacker(get_victim_entity())
                .build()
        );
    }
}