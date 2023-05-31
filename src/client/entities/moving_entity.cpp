#include "moving_entity.hpp"
#include <scene/3d/navigation_agent_3d.h>
#include <math.h>

MovingEntity::MovingEntity()
{
    //Setup navigation agent
    nav_agent = memnew(NavigationAgent3D);
    nav_agent->set_radius(pathfinding_radius);
    //Make it as accurate as possible
    nav_agent->set_path_desired_distance(0.1);
    nav_agent->set_target_desired_distance(0.1);

    add_child(nav_agent);

    SceneTree::get_singleton()->connect("physics_frame", callable_mp(this, &MovingEntity::movement_process_frame));
}
/**
 * Movement function called each frame
*/
void MovingEntity::movement_process_frame()
{
    
    if(nav_agent->is_navigation_finished())
		return;

    double delta = SceneTree::get_singleton()->get_physics_process_time();

	float movement_delta = stats.movementSpeed * delta;
	Vector3 next_path_position = nav_agent->get_next_path_position();
	Vector3 current_position = get_global_position();
	Vector3 new_velocity = (next_path_position - current_position).normalized() * movement_delta;
	set_global_position(get_global_position() + new_velocity);
    //FIXME: Rotation looks clunky
    //NOTE: Facing direction (0,0,0) looking towards "-Z"
    look_at(nav_agent->get_next_path_position());
}

void MovingEntity::set_movement_target_position(Vector3 target_pos)
{
    nav_agent->set_target_position(target_pos);
}

Vector3 MovingEntity::get_movement_target_position()
{
    return nav_agent->get_target_position();
}