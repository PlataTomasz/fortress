#include <shared/abilities/barbarian/barbarian_lacerating_slash_ability.h>
#include <shared/collisions/ability_hitbox_helper.h>
#include <shared/gamemodes/gamemode.h>
#include <shared/core/game_level.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/data_holders/builders/damage_object_builder.h>

void BarbarianLaceratingSlashAbility::_use(const Ref<ActionContext> &use_context) {
    AbilityHitboxHelper area_helper = AbilityHitboxHelper(slash_area);
    ERR_FAIL_NULL(use_context->get_user()->get_gamelevel());
    Gamemode *gamemode = use_context->get_user()->get_gamelevel()->get_gamemode();

    for(Entity *ent : area_helper.get_entities_in_area() ) {
        DamageableComponent *damageable = ent->get_damageable_component();
        if(damageable && gamemode && gamemode->is_entity_enemy_of(use_context->get_user(), ent)) {
            damageable->take_damage(
                DamageObjectBuilder()
                    .attacker(use_context->get_user())
                    .value(base_damage)
                    .damage_subtype_ability()
                    .damage_subtype_area()
                    .damage_type(DamageObject::DamageType::DAMAGE_PHYSICAL)
                    .build()
            );
        }
    }
}