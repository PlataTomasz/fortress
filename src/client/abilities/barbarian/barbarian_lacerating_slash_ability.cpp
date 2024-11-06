#include <shared/abilities/barbarian/barbarian_lacerating_slash_ability.h>
#include <shared/collisions/ability_hitbox_helper.h>
#include <shared/gamemodes/gamemode.h>
#include <shared/core/game_level.h>

void BarbarianLaceratingSlashAbility::_use(const Ref<ActionContext> &use_context) {
    ERR_FAIL_NULL(use_context->get_user());
    // Play VFX matching area
    play_vfx(use_context, slash_area_vfx);

    // Play sound on use
    play_sound(use_context, sword_swing_sound);
    
    ERR_FAIL_NULL(use_context->get_user()->get_gamelevel());
    Gamemode *gamemode = use_context->get_user()->get_gamelevel()->get_gamemode();

    AbilityHitboxHelper area_helper = AbilityHitboxHelper(slash_area);
    bool at_least_one_entity_was_hit = false;
    for(Entity *potential_target_entity : area_helper.get_entities_in_area()) {
        if(gamemode && gamemode->is_entity_enemy_of(use_context->get_user(), potential_target_entity)) {
            _slash_hit_entity(potential_target_entity);
            at_least_one_entity_was_hit = true;
        }
    }

    if(at_least_one_entity_was_hit) {
        play_sound(use_context, hit_sound);
    }
}

void BarbarianLaceratingSlashAbility::_slash_hit_entity(Entity *entity) {
    ERR_FAIL_NULL(entity);
    // Play VFX on each hit entity
    play_vfx_at_position(slash_hit_vfx, entity->get_global_position());
}