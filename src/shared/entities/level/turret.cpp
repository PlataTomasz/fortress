#include "turret.h"

#include <scene/3d/area_3d.h>
#include <shared/entities/projectile_entity.h>
#include <shared/core/game_level.h>

void Turret::fire_projectile_at(Entity *projectile_target) {
    GameLevel *game_level = projectile_target->get_gamelevel();
    ERR_FAIL_NULL(game_level);

    ProjectileEntity *projectile_instance = Object::cast_to<ProjectileEntity>(projectile_template->instantiate());
    ERR_FAIL_NULL(projectile_instance);
    
    projectile_instance->set_position(this->get_position());
    projectile_instance->set_target(projectile_target);
    game_level->add_entity(projectile_instance);
}

void Turret::_on_area_enter_radius(Area3D *area) {
    /*
        When entity's hitbox enters turret range, It gets attacked once per 0.7s.
    */

    Entity *ent = Object::cast_to<Entity>(area->get_parent());
    if (!ent) return; // Not a valid target

    current_target = ent;

    // Every serval time units, a projectile is fired at target


    // Enable turret
    // turret_active = true;
}

void Turret::_on_attack_cooldown_pass() {
    fire_projectile_at(current_target);
}

void Turret::_init() {
    detection_area = static_cast<Area3D *>(get_node(NodePath("DetectionArea")));
}