#include <shared/abilities/orc/orc_leap_slam_ability.h>

#include <scene/animation/tween.h>
#include <scene/3d/physics/area_3d.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/data_holders/builders/damage_object_builder.h>
#include <shared/collisions/ability_hitbox_helper.h>
#include <shared/gamemodes/gamemode.h>
#include <shared/core/game_level.h>

void OrcLeapSlamAbility::_use(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(action_context->get_user());

    // Jump a bit into air and then slam area beneath
    Vector3 position_before_leap = action_context->get_user()->get_global_position();

    // Land to "position before" leap after 0.5s
    Ref<Tween> tween = create_tween();
    tween->tween_method(callable_mp((Node3D *)action_context->get_user(), &Node3D::set_global_position), position_before_leap + Vector3(0, 2, 0), position_before_leap, 0.5);
    tween->tween_callback(callable_mp(this, &OrcLeapSlamAbility::_slam).bind(action_context, position_before_leap));
}

void OrcLeapSlamAbility::_slam(const Ref<ActionContext>& action_context, const Vector3 &slam_position) {
    AbilityHitboxHelper area_helper = AbilityHitboxHelper(leap_slam_area);
    ERR_FAIL_NULL(action_context->get_user()->get_gamelevel());
    Gamemode *gamemode = action_context->get_user()->get_gamelevel()->get_gamemode();

    for(Entity *ent : area_helper.get_entities_in_area() ) {
        DamageableComponent *damageable = ent->get_damageable_component();
        if(damageable && gamemode && gamemode->is_entity_enemy_of(action_context->get_user(), ent)) {
            damageable->take_damage(
                DamageObjectBuilder()
                    .attacker(action_context->get_user())
                    .value(40)
                    .damage_subtype_ability()
                    .damage_subtype_area()
                    .damage_type(DamageObject::DamageType::DAMAGE_PHYSICAL)
                    .build()
            );
        }
    }
}

void OrcLeapSlamAbility::_slam_hit_entity(Entity *ent) {
    
}