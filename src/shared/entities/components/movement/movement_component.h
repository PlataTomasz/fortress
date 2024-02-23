#if !defined(MOVEMENT_COMPONENT_INCLUDED)
#define MOVEMENT_COMPONENT_INCLUDED

#include "../component.h"

class Node3D;
class NavigationAgent3D;
class EntityStatsComponent;

/**
 * Node, which instantes control movement of an Entity
*/
class MovementComponent : public Component
{
GDCLASS(MovementComponent, Component);
private:
    NavigationAgent3D *nav_agent = nullptr;

    float movement_speed = 2.0;

    void _tick();
    void _init();
    void _parented();
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    void set_pathfinding_radius(real_t pathfinding_radius);
    real_t get_pathfinding_radius();

    Vector3 get_destination_position();
    void set_destination_position(Vector3 target_pos);
};

#endif // MOVEMENT_COMPONENT_INCLUDED