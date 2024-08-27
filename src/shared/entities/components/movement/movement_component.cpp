#include "movement_component.h"
#include <scene/3d/navigation_agent_3d.h>
#include <scene/3d/node_3d.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/helper_macros.h>

#include <shared/string_names/component_stringnames.h>

#include <shared/entities/entity.h>

void MovementComponent::_notification(int p_notification) {
	DISABLE_IN_EDITOR();

	switch (p_notification) {
		case NOTIFICATION_PHYSICS_PROCESS:
			_tick();
			break;
		case NOTIFICATION_READY:
			break;
		case NOTIFICATION_PARENTED:
			_parented();
			break;
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			break;
		case NOTIFICATION_PROCESS:
			_frame();
			break;
		default:
			break;
	}
}
#ifdef SERVER
void MovementComponent::_tick() {
	if (nav_agent->is_navigation_finished()) {
		currently_moving = false;
		return;
	}

	currently_moving = true;

	Entity *ent = Object::cast_to<Entity>(get_parent());
	ERR_FAIL_NULL(ent);
	double delta = SceneTree::get_singleton()->get_physics_process_time();

	EntityAttributesComponent *attributes = ent->get_attributes_component();
	ERR_FAIL_NULL(attributes);

	// Normalize to somewhat match previous hardcoded value
	float movement_speed = attributes->get_movement_speed()->get_current() / 150;

	//NOTE: Currently fixed movement speed value is used
	float movement_delta = movement_speed * delta;
	Vector3 next_path_position = nav_agent->get_next_path_position();
	Vector3 current_position = ent->get_position();


	// Here is the source of bug

	Vector3 new_velocity = (next_path_position - current_position).normalized() * movement_delta;

	Vector3 new_position = current_position + new_velocity;
	// Check if target position is in certain range, if so, alter position so it wont move past the target
/* 	float distance_between_target_and_current = current_position.distance_to(next_path_position);

	if(distance_between_target_and_current <= nav_agent->get_target_desired_distance()) {
		Vector3 corrected_new_position = current_position + new_velocity;
		// Change
	} else {

	} */
	

	ent->set_position(current_position + new_velocity);
	//FIXME: Rotation looks clunky - interpolation?
	//NOTE: Facing direction (0,0,0) looking towards "-Z"
	if(ent->get_position() != next_path_position) // Sets facing direction // TODO: Move to Entity as a new method
		ent->look_at(next_path_position, Vector3(0, 1, 0), true);
		/*
		Vector3 corrected_rotation = ent->get_rotation();
		corrected_rotation.y = corrected_rotation.y + 180;
		ent->set_rotation(corrected_rotation);
		*/
}
#endif

#ifdef CLIENT
void MovementComponent::_tick() {
	// bool previous_currently_moving = currently_moving;
	// if(get_global_position() == previous_position ) {
	// 	currently_moving = false;
	// 	if(currently_moving != previous_currently_moving ) {
	// 		emit_signal("movement_finish");
	// 	}
	// } else {
	// 	currently_moving = true;
	// 	if(currently_moving != previous_currently_moving ) {
	// 		emit_signal("movement_started");
	// 	}
	// }
	// previous_position = get_global_position();
}
#endif

void MovementComponent::_frame() {
	
}

void MovementComponent::_parented() {
	Entity *ent = static_cast<Entity *>(get_parent());
	//ent->set_component(ComponentStringNames::get_singleton()->movement_component, this);
}

void MovementComponent::_init() {
	nav_agent = memnew(NavigationAgent3D);
	nav_agent->set_avoidance_enabled(true);
	add_child(nav_agent);

	set_physics_process(true);
	set_process(true);
}

bool MovementComponent::is_currently_moving() {
	return currently_moving;
}

void MovementComponent::set_currently_moving(bool new_currently_moving) {
	bool old_currently_moving = currently_moving;
	currently_moving = new_currently_moving;

	DISABLE_IN_EDITOR();
	if(old_currently_moving == true && new_currently_moving == false) {
		emit_signal("movement_finish");
	} else if(old_currently_moving == false && new_currently_moving == true) {
		emit_signal("movement_started");
	}
}

void MovementComponent::set_destination_position(Vector3 target_position) {
	nav_agent->set_target_position(target_position);
}

Vector3 MovementComponent::get_destination_position() {
	return nav_agent->get_target_position();
}

void MovementComponent::_bind_methods() {
	ADD_SIGNAL(MethodInfo("currently_moving_changed", PropertyInfo(Variant::BOOL, "is_moving")));
	ADD_SIGNAL(MethodInfo("movement_started"));
	ADD_SIGNAL(MethodInfo("movement_finish"));

	ClassDB::bind_method(D_METHOD("is_currently_moving"), &MovementComponent::is_currently_moving);
    ClassDB::bind_method(D_METHOD("set_currently_moving", "currently_moving"), &MovementComponent::set_currently_moving);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "currently_moving"), "set_currently_moving", "is_currently_moving");
}

void MovementComponent::set_pathfinding_radius(real_t pathfinding_radius) {
    nav_agent->set_radius(pathfinding_radius);
}

real_t MovementComponent::get_pathfinding_radius() {
    return nav_agent->get_radius();
}