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
private:
    //Node cache - faster than get_node()
    Node3D *parent_node3d = nullptr;
    NavigationAgent3D *nav_agent = nullptr;
    EntityStatsComponent *stat_component = nullptr;

    Vector<String> _get_configuration_warnings();

    void _physics_process();
protected:
    void _notification(int p_notification);
    void _on_sibling_added(Node *sibling);
    void _on_sibling_removed(Node *sibling);
    void _on_parent_changed() override;
    void _on_child_added(Node *node) override;
    void _on_child_removed(Node *node) override;
public:
    void set_pathfinding_radius(real_t pathfinding_radius);
    real_t get_pathfinding_radius();

    Vector3 get_destination_position();
    void set_destination_position(Vector3 target_pos);
};

#endif // MOVEMENT_COMPONENT_INCLUDED