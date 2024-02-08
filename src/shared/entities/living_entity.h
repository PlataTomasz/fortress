#if !defined(LIVING_ENTITY)
#define LIVING_ENTITY

#include <shared/entities/entity.h>

class NavigationAgent3D;

/**
 * Entity specialization which includes movement
*/
class LivingEntity : public Entity
{
protected:
    NavigationAgent3D* nav_agent = nullptr;
    //How big is entity for pathfinding purposes?
    double pathfinding_radius = 0.5;

    void movement_process_frame();

    void _notification(int p_notification);
public:
    void set_movement_target_position(Vector2 target_pos);
    Vector3 get_movement_target_position();
};

#endif // LIVING_ENTITY
