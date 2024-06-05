#include "movement_component.h"
#include <scene/3d/navigation_agent_3d.h>
#include <scene/3d/node_3d.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/helper_macros.h>

#include <shared/string_names/component_stringnames.h>

#include <shared/entities/entity.h>

#include <shared/entities/traits/t_has_attributes.h>

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
		default:
			break;
	}
}
#ifdef SERVER
void MovementComponent::_tick() {
	if (nav_agent->is_target_reached()) {
		return;
	}

	Entity *ent = static_cast<Entity *>(get_parent());
	double delta = SceneTree::get_singleton()->get_physics_process_time();

	THasAttributes *t_has_attributes = dynamic_cast<THasAttributes *>(get_parent());
	ERR_FAIL_NULL(t_has_attributes);

	EntityAttributesComponent *attributes = t_has_attributes->get_attributes_component();
	ERR_FAIL_NULL(attributes);

	// Normalize to somewhat match previous hardcoded value
	float movement_speed = attributes->get_movement_speed()->get_current() / 150;

	//NOTE: Currently fixed movement speed value is used
	float movement_delta = movement_speed * delta;
	Vector3 next_path_position = nav_agent->get_next_path_position();
	Vector3 current_position = ent->get_position();
	Vector3 new_velocity = (next_path_position - current_position).normalized() * movement_delta;
	ent->set_position(current_position + new_velocity);
	//FIXME: Rotation looks clunky - interpolation?
	//NOTE: Facing direction (0,0,0) looking towards "-Z"
	if(ent->get_position() != next_path_position)
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
	
}
#endif

void MovementComponent::_parented() {
	Entity *ent = static_cast<Entity *>(get_parent());
	//ent->set_component(ComponentStringNames::get_singleton()->movement_component, this);
}

void MovementComponent::_init() {
	nav_agent = memnew(NavigationAgent3D);
	nav_agent->set_avoidance_enabled(true);
	add_child(nav_agent);

	set_physics_process(true);
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