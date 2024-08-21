#include "turret.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <scene/3d/physics/area_3d.h>
#include <shared/core/game_level.h>
#include <shared/entities/entity.h>
#include <shared/entities/projectile_entity.h>
#include <scene/main/timer.h>
#include <scene/resources/packed_scene.h>

void Turret::_initv() {
    attack_cooldown_counter = memnew(Timer);
    attack_cooldown_counter->set_autostart(true);
    attack_cooldown_counter->connect("timeout", callable_mp(this, &Turret::_attack_off_cooldown));
    add_child(attack_cooldown_counter);
}

void Turret::_attack_off_cooldown() {
    if(has_target()) {
        attack_current_target();
    }
}

void Turret::attack_current_target() {
    ERR_FAIL_NULL(current_target);

    GameLevel *game_level = current_target->get_gamelevel();
    ERR_FAIL_NULL(game_level);

    ProjectileEntity *projectile_instance = Object::cast_to<ProjectileEntity>(projectile_template->instantiate());
    ERR_FAIL_NULL(projectile_instance);
    
    projectile_instance->set_position(this->get_position());
    projectile_instance->set_target(current_target);
    projectile_instance->set_creator(this);
    game_level->add_entity(projectile_instance);
}

Entity *Turret::find_new_target() {
    /*
    1. Search aggro area for potential target by selecting any entity in aggro area
    2. Select other entity in aggro area, if there are no other entities, jump to step 4.
    3. If entity selected in step 2 has higher aggro priotity than entity in step 1, it becomes new potential target
    4. Back to step 2
    5. Return potential target
    */

    return get_closest_entity(aggro_area->get_entities_in_area());;
}

Entity *Turret::get_closest_entity(const Vector<Entity *> &potential_closest_entities) {
	ERR_FAIL_COND_V(!(potential_closest_entities.size() > 0), nullptr);

    struct ClosestEntityData {
        Entity *entity = nullptr;
        float squared_distance_to = 0;
    } closest_entity_data;

    // TODO: Create GameCordinates class to store position of entity with possible ignore of y axis, to make easier messing with coordinates

	for (int potential_closest_index = 0; potential_closest_index < potential_closest_entities.size(); potential_closest_index++) {
        Entity *potential_closest_entity = potential_closest_entities[potential_closest_index];
        float potential_closest_entity_distance = potential_closest_entity->get_position_2d().distance_squared_to(this->get_position_2d());

		if (potential_closest_entity_distance < closest_entity_data.squared_distance_to) {
            closest_entity_data.entity = potential_closest_entity;
            closest_entity_data.squared_distance_to = potential_closest_entity_distance;
		}
	}

	return closest_entity_data.entity;
}

int get_higher_aggro_priority(int first_aggro_priority, int second_aggro_priority) {
    if(first_aggro_priority > second_aggro_priority) {
        return first_aggro_priority;
    } else if(second_aggro_priority >= first_aggro_priority) {
        return second_aggro_priority;
    } else {
        return second_aggro_priority;
    }
}

int Turret::get_aggro_priority_for_entity(Entity *entity) {
    if(entity->has_tag("Mercenary")) {
        return 1;
    } else if(entity->has_tag("Minion")) {
        return 0;
    } else {
        return 1000;
    }
}

void Turret::change_target(Entity *new_target) {
    current_target = new_target;
}

void Turret::_on_entity_left_aggro_area(Entity *entity_that_left) {
    if(entity_that_left == current_target) {
        _on_target_left_aggro_area();
    }
}

void Turret::_on_target_left_aggro_area() {
    current_target = find_new_target();
}

bool Turret::is_entity_valid_target(Entity *potential_target) {
    if(potential_target->get_damageable_component()) {
        return true;
    } else {
        return false;
    }
}

bool Turret::has_target() {
    return (current_target != nullptr);
}

void Turret::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_aggro_area"), &Turret::get_aggro_area);
    ClassDB::bind_method(D_METHOD("set_aggro_area", "aggro_area"), &Turret::set_aggro_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aggro_area", PROPERTY_HINT_NODE_TYPE, AdvancedArea3D::get_class_static()), "set_aggro_area", "get_aggro_area");

    ClassDB::bind_method(D_METHOD("get_cooldown_between_attacks"), &Turret::get_cooldown_between_attacks);
    ClassDB::bind_method(D_METHOD("set_cooldown_between_attacks", "cooldown_between_attacks"), &Turret::set_cooldown_between_attacks);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldown_between_attacks"), "set_cooldown_between_attacks", "get_cooldown_between_attacks");

    ClassDB::bind_method(D_METHOD("get_projectile_template"), &Turret::get_projectile_template);
    ClassDB::bind_method(D_METHOD("set_projectile_template", "projectile_template"), &Turret::set_projectile_template);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "projectile_template", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_projectile_template", "get_projectile_template");
}

void Turret::_on_entity_enter_aggro_area(Entity *entity_that_entered) {
    if(!has_target() && is_entity_valid_target(entity_that_entered)) {
        current_target = entity_that_entered;
    }
}

void Turret::set_aggro_area(AdvancedArea3D *new_aggro_area) {
    aggro_area = new_aggro_area;
    if(aggro_area) {
        aggro_area->connect("entity_entered", callable_mp(this, &Turret::_on_entity_enter_aggro_area));
        aggro_area->connect("entity_exited", callable_mp(this, &Turret::_on_entity_left_aggro_area));
    }
}

AdvancedArea3D *Turret::get_aggro_area() {
    return aggro_area;
}

void Turret::set_cooldown_between_attacks(float new_cooldown) {
    cooldown_between_attacks = new_cooldown;
    DISABLE_IN_EDITOR();
    attack_cooldown_counter->set_wait_time(new_cooldown);
}

float Turret::get_cooldown_between_attacks() {
    return cooldown_between_attacks;
}

void Turret::set_projectile_template(const Ref<PackedScene>& new_projectile_template) {
    projectile_template = new_projectile_template;
}

Ref<PackedScene> Turret::get_projectile_template() {
    return projectile_template;
}
