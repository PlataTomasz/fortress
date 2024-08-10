#if !defined(PROJECTILE_ENTITY_INCLUDED)
#define PROJECTILE_ENTITY_INCLUDED

#include <shared/entities/entity.h>

class ProjectileEntity : public Entity {
GDCLASS(ProjectileEntity, Entity);
private:
    Entity *target = nullptr;
    // AI = Move toward target with constat speed and deal damage on impact
protected:
    static void _bind_methods();

    void _tickv() override;
public:
    void set_target(Entity *new_target);
    Entity *get_target();
};

#endif // PROJECTILE_ENTITY_INCLUDED
