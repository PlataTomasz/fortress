#include <shared/abilities/barbarian/barbarian_intimidating_cry_ability.h>

#include <scene/3d/physics/area_3d.h>
#include <shared/status_effects/status_effect.hpp>
#include <shared/registries/status_effect_registry.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>

void BarbarianIntimidatingCryAbility::_use(const Ref<ActionContext> &use_context) {
    ERR_FAIL_NULL(warcry_area);
    ERR_FAIL_NULL(use_context->get_user());

    TypedArray<Area3D> overlapping_areas = warcry_area->get_overlapping_areas();

    for(int i = 0;i<overlapping_areas.size();i++) {
        Area3D *area = Object::cast_to<Area3D>(overlapping_areas[i].operator Object *());
        ERR_CONTINUE(!area);

        Entity *ent = Object::cast_to<Entity>(area->get_parent());
        ERR_CONTINUE(!ent);

        StatusEffectVictimComponent *status_effect_victim = ent->get_status_effect_victim_component();
        ERR_CONTINUE(!status_effect_victim);

        // TODO: Should only affect enemies - check if user is hostile toward target entity
        StatusEffect *status_effect_instance = StatusEffectRegistry::get_singleton()->create_instance("barbarian_intimidating_cry_debuff");
        ERR_CONTINUE(!status_effect_instance);

        status_effect_instance->set_inflictor(use_context->get_user());

        status_effect_victim->apply_status_effect(status_effect_instance);
    }
}