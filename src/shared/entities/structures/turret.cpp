#include "turret.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <scene/3d/area_3d.h>

void Turret::_initv() {

}

Entity *Turret::find_new_target() {
    /*
    1. Search aggro area for potential target by selecting any entity in aggro area
    2. Select other entity in aggro area, if there are no other entities, jump to step 4.
    3. If entity selected in step 2 has higher aggro priotity than entity in step 1, it becomes new potential target
    4. Back to step 2
    5. Return potential target
    */
    Vector<Entity *> entities_in_area; // TODO: Currently null

    Entity *closest_entity = get_closest_entity(entities_in_area);

    Entity *new_target = nullptr;
    int new_target_aggro_priority = 0;
    for(Entity *potential_target : entities_in_area) {
        if(new_target_aggro_priority > ) {
            
        }
    }

    return new_target;
}

bool Turret::are_entities_aggro_priority_equal() {
    //if(first_aggro_)
    return false;
}

Entity *Turret::get_closest_entity(const Vector<Entity *> &potential_closest_entities) {
	ERR_FAIL_COND_V(!(potential_closest_entities.size() > 0), nullptr);

    struct ClosestEntityData {
        Entity *entity = nullptr;
        float squared_distance_to = 0;
    } closest_entity_data;

	closest_entity_data.entity = potential_closest_entities[0];
    closest_entity_data.squared_distance_to = closest_entity_data.entity->get_position_2d().distance_squared_to(this->get_position_2d());

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

void Turret::_on_target_left_aggro_area() {
    Entity *current_target = find_new_target();
}

bool Turret::is_entity_valid_target(Entity *potential_target) {
    if(potential_target->get_component<DamageableComponent>() != nullptr) {
        return true;
    } else {
        return false;
    }
}

bool Turret::has_target() {
    return (current_target != nullptr);
}

void Turret::_on_entity_enter_aggro_area(Entity *entity_that_entered) {
    if(!has_target() && is_entity_valid_target(entity_that_entered)) {
        current_target = entity_that_entered;
    }
}