#if !defined(PROJECTILE_ENTITY_INCLUDED)
#define PROJECTILE_ENTITY_INCLUDED

#include <shared/entities/entity.h>
class Area3D;

class ProjectileEntity : public Entity {
GDCLASS(ProjectileEntity, Entity);
private:
    Entity *creator = nullptr;
    Entity *target = nullptr;

    Area3D *hitbox = nullptr;

    void _on_hit_detect(Area3D *detected_area);
    // AI = Move toward target with constat speed and deal damage on impact
protected:
    static void _bind_methods();

    void _tickv() override;
    void _readyv() override;
    virtual void _on_hit_entity(Entity *hit_entity);
public:
    void set_target(Entity *new_target);
    Entity *get_target();

    void set_creator(Entity *new_creator);
    Entity *get_creator();

    void set_hitbox(Area3D *new_hitbox);
    Area3D *get_hitbox();
};

#endif // PROJECTILE_ENTITY_INCLUDED
