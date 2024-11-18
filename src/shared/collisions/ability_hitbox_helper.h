#if !defined(ABILITY_HITBOX_HELPER_INCLUDED)
#define ABILITY_HITBOX_HELPER_INCLUDED

#include <scene/3d/physics/area_3d.h>

class AbilityHitboxHelper {
private:
    Area3D *area = nullptr;
public:
    List<Entity *> get_allies_in_area() {
        TypedArray<Area3D> areas = area->get_overlapping_areas();
        for(int i = 0;i<areas.size();i++) {
            Area3D *caught_area = Object::cast_to<Area3D>(areas.get(i).operator Object *());
            ERR_CONTINUE(caught_area);

            Entity *ent = Object::cast_to<Entity>(caught_area->get_parent());
            if(!ent) continue;

            

            // I need to know to which team this entity belongs to

        }

        return List<Entity *>();
    }

    List<Entity *> get_enemies_in_area() {
        return List<Entity *>();
    }

    List<Entity *> get_entities_in_area() {
        List<Entity *> entities;

        TypedArray<Area3D> areas = area->get_overlapping_areas();
        for(int i = 0;i<areas.size();i++) {
            Area3D *caught_area = Object::cast_to<Area3D>(areas.get(i).operator Object *());
            ERR_CONTINUE(!caught_area);

            if(!caught_area->is_in_group("hurtbox")) continue; // Catch only hurtboxes

            Entity *ent = Object::cast_to<Entity>(caught_area->get_parent());
            if(!ent) continue;

            entities.push_back(ent);
        }

        return entities;
    }

    AbilityHitboxHelper(Area3D *new_area) {
        area = new_area;
    }
};

#endif // ABILITY_HITBOX_HELPER_INCLUDED
