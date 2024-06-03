#include "barbarian_basic_attack.h"

#include <scene/3d/area_3d.h>

void BarbarianBasicAttack::use(const Ref<ActionContext>& use_context) {
    TypedArray<Node> areas = hitbox->get_overlapping_areas();

    for(int i = 0;i<areas.size();i++) {
        Area3D *area = static_cast<Area3D *>(areas[i].operator Object *());

        // Deal damage to every caught unit
        
    }
}