#include "orc_warhorn.h"

#include <scene/3d/area_3d.h>
#include <core/variant/variant.h>
#include <shared/status_effects/status_effect.hpp>
#include <shared/core/managers/component_manager.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/status_effects/status_effect_factory.h>

void OrcWarhornAbility::use_impl() {
    Vector3 use_position;
    
    Area3D *buff_hitarea = nullptr;
    //Area3DFactory::create_radius_area(radius);
    TypedArray<Area3D> areas = buff_hitarea->get_overlapping_areas();
    
	for (int i = 0; i < areas.size(); i++) {
        Area3D *colliding_area = static_cast<Area3D *>(areas[i].get_validated_object());
        StatusEffect *status_effect = StatusEffectFactory::create_status_effect("orc_warhorn_buff");


        StatusEffectVictimComponent *status_effect_component = ComponentManager::get_component<StatusEffectVictimComponent>(colliding_area->get_parent());

        if (status_effect_component) {
            status_effect_component->apply_status_effect(status_effect);
        }
	}
};