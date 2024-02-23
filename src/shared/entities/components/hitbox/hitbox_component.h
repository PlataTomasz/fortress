#if !defined(HITBOX_COMPONENT_INCLUDED)
#define HITBOX_COMPONENT_INCLUDED

#include <shared/entities/components/component_3d.h>

class Area3D;
class CollisionShape3D;

class HitboxComponent : public Component3D {
public:
    Area3D *area = nullptr;
    CollisionShape3D *collision_shape = nullptr;
private:
    void _init();

    void _hitbox_entered(Area3D *p_area);
    void _hitbox_leave(Area3D *p_area);
protected:
};

#endif // HITBOX_COMPONENT_INCLUDED
