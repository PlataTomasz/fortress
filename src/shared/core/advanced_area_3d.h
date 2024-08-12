#if !defined(ADVANCED_AREA_3D_INCLUDED)
#define ADVANCED_AREA_3D_INCLUDED

#include <scene/3d/area_3d.h>

class Entity;

class AdvancedArea3D : public Area3D {
GDCLASS(AdvancedArea3D, Area3D);
private:
    void _hitbox_entered(Area3D *p_area);
    void _hitbox_exited(Area3D *p_area);
protected:
    static void _bind_methods();
    void _notification(int p_notification);
public:
    Vector<Entity *> get_entities_in_area();
};

#endif // ADVANCED_AREA_3D_INCLUDED
