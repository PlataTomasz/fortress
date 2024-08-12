#include "turret_attack_ability.h"

#include <shared/core/game_level.h>

void TurretAttackAbility::_use(const Ref<ActionContext>& action_context) {
    action_context->get_target_entity();

    // Spawn delayed explosion at target entity's position

    Entity *user = action_context->get_user();
    ERR_FAIL_NULL(user);

    GameLevel *game_level = user->get_gamelevel();
    ERR_FAIL_NULL(game_level);

    Entity *turret_projectile_instance = Object::cast_to<Entity>(turret_projectile_template->instantiate());
    ERR_FAIL_NULL(turret_projectile_instance);

    turret_projectile_instance->set_position(user->get_position());

    game_level->add_entity(turret_projectile_instance);
}