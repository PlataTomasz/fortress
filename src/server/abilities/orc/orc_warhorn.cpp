#include <shared/abilities/orc/orc_warhorn.h>

#include <scene/3d/physics/area_3d.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/status_effects/status_effect.hpp>
#include <shared/registries/status_effect_registry.h>

void OrcWarhornAbility::_use(const Ref<ActionContext>& action_context) {
	ERR_FAIL_NULL(buff_hitarea);
    ERR_FAIL_NULL(action_context->get_user());
	Vector3 use_position;
	//Area3DFactory::create_radius_area(radius);
	TypedArray<Area3D> areas = buff_hitarea->get_overlapping_areas();

	for (int i = 0; i < areas.size(); i++) {
		Area3D *colliding_area = static_cast<Area3D *>(areas[i].get_validated_object());

        Entity *ent = Object::cast_to<Entity>(colliding_area->get_parent());
        ERR_CONTINUE(!ent);

		StatusEffectVictimComponent *status_effect_component = ent->get_status_effect_victim_component();
        ERR_CONTINUE(!status_effect_component);

		StatusEffect *status_effect = Registry<StatusEffect>::get_singleton()->create_instance("orc_warhorn_buff");
        status_effect->set_inflictor(action_context->get_user());
		status_effect_component->apply_status_effect(status_effect);
	}
};