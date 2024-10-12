#include "barbarian_basic_attack.h"

#include <scene/3d/physics/area_3d.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/entities/components/visual/visual_component_3d.h>
#include <scene/main/timer.h>

void BarbarianBasicAttack::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_hitbox"), &BarbarianBasicAttack::get_hitbox);
    ::ClassDB::bind_method(D_METHOD("set_hitbox"), &BarbarianBasicAttack::set_hitbox);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hitbox", PROPERTY_HINT_NODE_TYPE, HitboxComponent::get_class_static()), "set_hitbox", "get_hitbox");

    ::ClassDB::bind_method(D_METHOD("get_hit_visual_effect"), &BarbarianBasicAttack::get_hit_visual_effect);
    ::ClassDB::bind_method(D_METHOD("set_hit_visual_effect"), &BarbarianBasicAttack::set_hit_visual_effect);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hit_visual_effect", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_hit_visual_effect", "get_hit_visual_effect");

    ::ClassDB::bind_method(D_METHOD("get_attack_area_vfx"), &BarbarianBasicAttack::get_attack_area_vfx);
    ::ClassDB::bind_method(D_METHOD("set_attack_area_vfx"), &BarbarianBasicAttack::set_attack_area_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attack_area_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_attack_area_vfx", "get_attack_area_vfx");
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
#ifdef SERVER
void BarbarianBasicAttack::_use(const Ref<ActionContext>& use_context) {
    _prepare_attack(use_context);

    List<HitboxComponent *> hitboxes = hitbox->get_overlapping_hitboxes();

    for(HitboxComponent *detected_hitbox : hitboxes) {
        Entity *ent = detected_hitbox->get_owning_entity();
        ERR_CONTINUE(!ent);

        if(ent == use_context->get_user()) continue; // Prevent hitting yourself

        print_line(use_context->get_user(), "attacked", ent);

        _entity_hit_with_attack(ent, use_context);
    }
}
#endif
void BarbarianBasicAttack::set_hit_visual_effect(const Ref<PackedScene> &new_hit_visual_effect) {
    hit_visual_effect = new_hit_visual_effect;
}

Ref<PackedScene> BarbarianBasicAttack::get_hit_visual_effect() {
    return hit_visual_effect;
}

void BarbarianBasicAttack::set_attack_area_vfx(const Ref<PackedScene> &new_attack_area_vfx) {
    attack_area_vfx = new_attack_area_vfx;
}

Ref<PackedScene> BarbarianBasicAttack::get_attack_area_vfx() {
    return attack_area_vfx;
}

void BarbarianBasicAttack::set_hitbox(HitboxComponent *p_hitbox) {
    hitbox = p_hitbox;
}

HitboxComponent *BarbarianBasicAttack::get_hitbox() {
    return hitbox;
}

#ifdef CLIENT
void BarbarianBasicAttack::_entity_hit_with_attack(Entity *entity, const Ref<ActionContext>& use_context) {
    Node3D *visual_effect = Object::cast_to<Node3D>(hit_visual_effect->instantiate());
    if(visual_effect) {
        // Tell clients that ent got hit by this ability
        entity->add_child(visual_effect);
    }
}

void BarbarianBasicAttack::_use(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(action_context->get_user());
    // Play swing sound
    
    // Play animation
    // TODO: Move to sandboxed method
    VisualComponent3D *visual_component = action_context->get_user()->get_visual_component();
    _prepare_attack(action_context);
    if(visual_component)  {
        visual_component->play_animation_override("Attack002");
    }
    else {
        print_error("Failed to play animation! Missing VisualComponent3D!");
    }
}


void BarbarianBasicAttack::_prepare_attack(const Ref<ActionContext>& action_context) {
    // Append attack VFX to attacker
    Node3D *visual_effect_instance = Object::cast_to<Node3D>(attack_area_vfx->instantiate());
    ERR_FAIL_NULL(visual_effect_instance);

    // Make it disappear when attack finishes
    Timer *timer = memnew(Timer);
    timer->set_wait_time(0.5);
    timer->set_autostart(true);
    timer->connect("timeout", callable_mp((Node *)visual_effect_instance, &Node::queue_free));

    visual_effect_instance->add_child(timer);

    add_child(visual_effect_instance);
}
#endif

#ifdef SERVER
void BarbarianBasicAttack::_entity_hit_with_attack(Entity *entity, const Ref<ActionContext>& use_context) {
    DamageableComponent *damageable = entity->get_damageable_component();
    if(damageable) {
        // TODO: Area of Effect is the inflictor, which is created by this ability. It's not ability itself that deals damage!
        damageable->take_damage(memnew(DamageObject(DamageObject::DAMAGE_PHYSICAL, (DamageObject::BASIC_ATTACK_DAMAGE), 15, use_context->get_user())));
    }
}

void BarbarianBasicAttack::_prepare_attack(const Ref<ActionContext>& action_context) {
    // Nothing happens currently, but this is where hit area of attack should be initialized

}
#endif