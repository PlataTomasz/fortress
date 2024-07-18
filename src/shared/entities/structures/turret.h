#if !defined(TURRET_INCLUDED)
#define TURRET_INCLUDED

#include <shared/entities/entity.h>
#include <scene/3d/area_3d.h>

class Turret : public Entity {
GDCLASS(Turret, Entity);
private:
    Entity *current_target = nullptr;

    Area3D *aggro_area = nullptr;
    
    void _on_target_left_aggro_area();
    void _on_entity_enter_aggro_area(Entity *entity_that_entered);
protected:
    void _initv() override;
public:
    bool has_target();
    bool is_entity_valid_target(Entity *potential_target);

    Entity *find_new_target();
    int get_aggro_priority_for_entity(Entity *entity);
    void change_target(Entity *new_target);
};

#endif // TURRET_INCLUDED
