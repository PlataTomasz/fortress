#include <shared/abilities/orc/orc_brute_force.h>

#include <scene/3d/physics/area_3d.h>
#include <scene/3d/physics/collision_shape_3d.h>
#include <scene/resources/3d/box_shape_3d.h>
#include <shared/entities/components/damage/damageable_component.h>

void OrcBruteForce::_use(const Ref<ActionContext> &action_context) {
    ERR_FAIL_NULL(brute_force_area);

    TypedArray<Area3D> areas_in_brute_force_range ;
    for(int i = 0;i<areas_in_brute_force_range.size();i++) {
        Area3D *area = Object::cast_to<Area3D>(areas_in_brute_force_range.get(i).operator Object *());
        ERR_CONTINUE(!area);

        Entity *ent = Object::cast_to<Entity>(area->get_parent());
        ERR_CONTINUE(!ent);

        DamageableComponent *damageable = ent->get_damageable_component();
        ERR_CONTINUE(damageable);

        damageable->take_damage(memnew(DamageObject(
            DamageObject::DamageType::DAMAGE_PHYSICAL, 
            (DamageObject::DamageSubtype::AREA_DAMAGE 
                & DamageObject::DamageSubtype::ABILITY_DAMAGE),
            hit_damage,
            action_context->get_user()
        )));
    }
}