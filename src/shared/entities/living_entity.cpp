#include "living_entity.h"
#include <scene/3d/navigation_agent_3d.h>

void LivingEntity::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_PHYSICS_PROCESS:
        {
            
        }
        break;
    
    case NOTIFICATION_READY:
        {
            nav_agent = memnew(NavigationAgent3D);
            nav_agent->set_radius(pathfinding_radius);
            //Make it as accurate as possible
            nav_agent->set_path_desired_distance(0.1);
            nav_agent->set_target_desired_distance(0.1);

            add_child(nav_agent);
        }
        break;

    default:
        break;
    }
}

void LivingEntity::movement_process_frame()
{
    if(nav_agent->is_navigation_finished())
		return;

    double delta = SceneTree::get_singleton()->get_physics_process_time();

	//float movement_delta = stats.movementSpeed * delta;
    //Placeholder - Stats API not yet migrated to serverside code
    float movement_delta = 2 * delta;

	Vector3 next_path_position = nav_agent->get_next_path_position();
	Vector3 current_position = get_global_position();
	Vector3 new_velocity = (next_path_position - current_position).normalized() * movement_delta;
	set_global_position(get_global_position() + new_velocity);
    //FIXME: Rotation looks clunky
    //NOTE: Facing direction (0,0,0) looking towards "-Z"
    look_at(nav_agent->get_next_path_position());
}

void LivingEntity::set_movement_target_position(Vector2 target_pos)
{
    nav_agent->set_target_position(Vector3(target_pos.x, 0, target_pos.y));
}

Vector3 LivingEntity::get_movement_target_position()
{
    return nav_agent->get_target_position();
}