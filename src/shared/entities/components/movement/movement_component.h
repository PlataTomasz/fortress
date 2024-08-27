#if !defined(MOVEMENT_COMPONENT_INCLUDED)
#define MOVEMENT_COMPONENT_INCLUDED

#include "../component_3d.h"

class Node3D;
class NavigationAgent3D;
class EntityStatsComponent;

/**
 * Node, which instantes control movement of an Entity
*/
class MovementComponent : public Component3D
{
GDCLASS(MovementComponent, Component3D);
private:
    bool currently_moving = false;

    NavigationAgent3D *nav_agent = nullptr;

    Vector3 previous_position;

    void _tick();
    void _init();
    void _parented();
    void _frame();
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    void set_currently_moving(bool new_currently_moving);
    bool is_currently_moving();

    void set_pathfinding_radius(real_t pathfinding_radius);
    real_t get_pathfinding_radius();

    Vector3 get_destination_position();
    void set_destination_position(Vector3 target_pos);
};

#endif // MOVEMENT_COMPONENT_INCLUDED