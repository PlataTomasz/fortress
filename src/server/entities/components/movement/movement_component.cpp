#include "movement_component.h"
#include <scene/3d/navigation_agent_3d.h>
#include <server/entities/components/entity_stats/entity_stat_component.h>
#include <scene/3d/node_3d.h>
#include <shared/helper_macros.h>

Vector<String> MovementComponent::_get_configuration_warnings()
{
    Vector<String> errors;

    if(nav_agent)
        errors.append("This node requires NavigationAgent3D for pathfinding puproses.");
    if(stat_component)
        errors.append("This node depends on StatComponent for movement speed stat - Add one as sibling");

    return errors;
}

void MovementComponent::_notification(int p_notification)
{
    DISABLE_IN_EDITOR();

    switch (p_notification)
    {
    case NOTIFICATION_PHYSICS_PROCESS:
    {
        _physics_process();
    }
    break;
    
    default:
        break;
    }
}

void MovementComponent::_physics_process()
{
    //Error protection
    IF_FALSE_RETURN(nav_agent);
    //Non-recoverable - component cannot move something without 3D position 
    IF_FALSE_RETURN(parent_node3d);
    //Cannot determine movement speed of entity
    IF_FALSE_RETURN(stat_component);


    //TODO: Interaction with displacement effects?
    //Movement related code here
    if(nav_agent->is_navigation_finished())
		return;

    double delta = SceneTree::get_singleton()->get_physics_process_time();

	float movement_delta = stat_component->get_movement_speed()->get_final_value() * delta;
	Vector3 next_path_position = nav_agent->get_next_path_position();
	Vector3 current_position = parent_node3d->get_global_position();
	Vector3 new_velocity = (next_path_position - current_position).normalized() * movement_delta;
	parent_node3d->set_global_position(current_position + new_velocity);
    //FIXME: Rotation looks clunky - interpolation?
    //NOTE: Facing direction (0,0,0) looking towards "-Z"
    parent_node3d->look_at(nav_agent->get_next_path_position());
}

void MovementComponent::_on_sibling_added(Node *sibling)
{
    if(EntityStatsComponent *stat_component_tmp = Object::cast_to<EntityStatsComponent>(sibling))
    {
        ERR_FAIL_COND_MSG(stat_component, "MovementComponent already has StatComponent reference. The first one will be used.");
    }
    
}

void MovementComponent::_on_sibling_removed(Node *sibling)
{
    if(sibling == stat_component)
        stat_component = nullptr;
}

void MovementComponent::_on_parent_changed()
{
    parent_node3d = Object::cast_to<Node3D>(get_parent());
}

void MovementComponent::_on_child_added(Node *node)
{
    NavigationAgent3D *nav_agent_tmp = Object::cast_to<NavigationAgent3D>(node);
    if(!nav_agent && nav_agent_tmp)
        nav_agent = nav_agent_tmp;
}

void MovementComponent::_on_child_removed(Node *node)
{
    if(node == nav_agent)
        nav_agent = nullptr;
}

void MovementComponent::set_destination_position(Vector3 target_position)
{
    ERR_FAIL_COND(!nav_agent);
    nav_agent->set_target_position(target_position);
}

Vector3 MovementComponent::get_destination_position()
{
    ERR_FAIL_COND_V(!nav_agent, Vector3());
    return nav_agent->get_target_position();
}
