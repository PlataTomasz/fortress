#if !defined(TURRET_INCLUDED)
#define TURRET_INCLUDED

#include <shared/entities/entity.h>

class Area3D;

/**
 * Turrets are strucutres, which are attacking any enemy entity that will enter It's range.
*/
class Turret : public Entity {
    Entity *current_target = nullptr;
    Area3D *detection_area = nullptr;
private:
    // New Area entered turret radius
    void _on_entity_enter_radius(Area3D *area);
    void _on_area_enter_radius(Area3D *area);

    void _init();
protected:
public:
};

#endif // TURRET_INCLUDED
