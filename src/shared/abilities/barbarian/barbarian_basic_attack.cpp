#include "barbarian_basic_attack.h"

#include <scene/3d/physics/area_3d.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/entities/components/visual/visual_component_3d.h>

void BarbarianBasicAttack::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_hitbox"), &BarbarianBasicAttack::get_hitbox);
    ::ClassDB::bind_method(D_METHOD("set_hitbox"), &BarbarianBasicAttack::set_hitbox);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hitbox", PROPERTY_HINT_NODE_TYPE, HitboxComponent::get_class_static()), "set_hitbox", "get_hitbox");
}

void BarbarianBasicAttack::_reparent_hitbox() {
    hitbox->reparent(get_ability_caster()->get_owning_entity());
}

void BarbarianBasicAttack::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
            //callable_mp(this, &BarbarianBasicAttack::_reparent_hitbox).call_deferred();
		} break;

		default:
			break;
	}
}

void BarbarianBasicAttack::_use(const Ref<ActionContext>& use_context) {
    List<HitboxComponent *> hitboxes = hitbox->get_overlapping_hitboxes();

    for(HitboxComponent *detected_hitbox : hitboxes) {
        Entity *ent = detected_hitbox->get_owning_entity();
        ERR_CONTINUE(!ent);

        if(ent == use_context->get_user()) continue; // Prevent hitting yourself

        print_line(use_context->get_user(), "attacked", ent);

        DamageableComponent *damageable = ent->get_damageable_component();
        if(damageable) {
            // TODO: Area of Effect is the inflictor, which is created by this ability. It's not ability itself that deals damage!
            damageable->take_damage(memnew(DamageObject(DamageObject::DAMAGE_PHYSICAL, (DamageObject::BASIC_ATTACK_DAMAGE), 15, use_context->get_user())));
        }
    }
}

#ifdef CLIENT
void BarbarianBasicAttack::_clientside_use(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(action_context->get_user());
    // Play swing sound
    
    // Play animation
    // TODO: Move to sandboxed method
    VisualComponent3D *visual_component = action_context->get_user()->get_visual_component();
    if(visual_component)  {
        visual_component->play_animation_override("Attack002");
    }
    else {
        print_error("Failed to play animation! Missing VisualComponent3D!");
    }
}
#endif

void BarbarianBasicAttack::set_hitbox(HitboxComponent *p_hitbox) {
    hitbox = p_hitbox;
}

HitboxComponent *BarbarianBasicAttack::get_hitbox() {
    return hitbox;
}