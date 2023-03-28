#if !defined(MOVING_ENTITY_HPP_INCLUDED)
#define MOVING_ENTITY_HPP_INCLUDED

#include "entity.hpp"

class NavigationAgent3D;

/**
 * Entity that can be issued with movement commands.
*/
class MovingEntity : public Entity
{
protected:
    NavigationAgent3D* nav_agent = nullptr;
    //How big is entity for pathfinding purposes?
    double pathfinding_radius = 0.5;

    void movement_process_frame();
public:
    void set_movement_target_position(Vector3 target_pos);
    Vector3 get_movement_target_position();

    MovingEntity();
};

#endif // MOVING_ENTITY_HPP_INCLUDED
