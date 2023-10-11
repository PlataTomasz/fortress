#if !defined(S_LIVING_ENTITY)
#define S_LIVING_ENTITY

#include <server/entities/s_base_entity.h>

class NavigationAgent3D;

/**
 * Entity specialization which includes movement
*/
class S_LivingEntity : public S_BaseEntity
{
protected:
    NavigationAgent3D* nav_agent = nullptr;
    //How big is entity for pathfinding purposes?
    double pathfinding_radius = 0.5;

    void movement_process_frame();

    void _notification(int p_notification);
public:
    void set_movement_target_position(Vector3 target_pos);
    Vector3 get_movement_target_position();
};

#endif // S_LIVING_ENTITY