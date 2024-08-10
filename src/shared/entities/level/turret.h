#if !defined(TURRET_INCLUDED)
#define TURRET_INCLUDED

#include <shared/entities/entity.h>
#include <scene/resources/packed_scene.h>

class Area3D;

/**
 * Turrets are strucutres, which are attacking any enemy entity that will enter It's range.
*/
class Turret : public Entity {
private:
    Entity *current_target = nullptr;
    Area3D *detection_area = nullptr;

    Ref<PackedScene> projectile_template;

    // New Area entered turret radius
    void _on_entity_enter_radius(Area3D *area);
    void _on_area_enter_radius(Area3D *area);

    void _on_attack_cooldown_pass();

    void _init();
protected:
public:
    void fire_projectile_at(Entity *projectile_target);
};

#endif // TURRET_INCLUDED
