#include "movement_component.h"
#include <scene/3d/navigation_agent_3d.h>
#include <scene/3d/node_3d.h>
#include <shared/entities/components/entity_stats/entity_stat_component.h>
#include <shared/helper_macros.h>

#include <shared/entities/entity.h>

void MovementComponent::_notification(int p_notification) {
	DISABLE_IN_EDITOR();

	switch (p_notification) {
		case NOTIFICATION_PHYSICS_PROCESS:
			_tick();
			break;
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			break;

		default:
			break;
	}
}

void MovementComponent::_tick() {
	if (nav_agent->is_target_reached()) {
		return;
	}

	Entity *ent = static_cast<Entity *>(get_parent());
	double delta = SceneTree::get_singleton()->get_physics_process_time();

	//NOTE: Currently fixed movement speed value is used
	float movement_delta = movement_speed * delta;
	Vector3 next_path_position = nav_agent->get_next_path_position();
	Vector3 current_position = ent->get_position();
	Vector3 new_velocity = (next_path_position - current_position).normalized() * movement_delta;
	ent->set_position(current_position + new_velocity);
	//FIXME: Rotation looks clunky - interpolation?
	//NOTE: Facing direction (0,0,0) looking towards "-Z"
	ent->look_at(nav_agent->get_next_path_position());
}

void MovementComponent::_init() {
	nav_agent = memnew(NavigationAgent3D);
	add_child(nav_agent);
}

void MovementComponent::set_destination_position(Vector3 target_position) {
	nav_agent->set_target_position(target_position);
}

Vector3 MovementComponent::get_destination_position() {
	return nav_agent->get_target_position();
}

void MovementComponent::_bind_methods() {
    
}

void MovementComponent::set_pathfinding_radius(real_t pathfinding_radius) {
    nav_agent->set_radius(pathfinding_radius);
}

real_t MovementComponent::get_pathfinding_radius() {
    return nav_agent->get_radius();
}