#if !defined(HITBOX_COMPONENT_INCLUDED)
#define HITBOX_COMPONENT_INCLUDED

#include <shared/entities/components/component_3d.h>
#include <scene/3d/area_3d.h>

class Entity;

class HitboxComponent : public Area3D {
GDCLASS(HitboxComponent, Area3D);
private:
    // Internal
    void _on_hitbox_entered(Area3D *p_area);
    void _on_hitbox_exited(Area3D *p_area);

    void _ready();
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    Entity *get_owning_entity();
    List<HitboxComponent *> get_overlapping_hitboxes();

    HitboxComponent() {
        
    }
};

#endif // HITBOX_COMPONENT_INCLUDED
