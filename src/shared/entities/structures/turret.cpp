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