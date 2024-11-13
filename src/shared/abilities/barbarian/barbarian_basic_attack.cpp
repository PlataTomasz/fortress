#include "barbarian_basic_attack.h"

#include <scene/3d/physics/area_3d.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/entities/components/visual/visual_component_3d.h>
#include <scene/main/timer.h>
#include <shared/core/game_level.h>
#include <shared/gamemodes/gamemode.h>

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

    ::ClassDB::bind_method(D_METHOD("get_slash_vfx_origin"), &BarbarianBasicAttack::get_slash_vfx_origin);
    ::ClassDB::bind_method(D_METHOD("set_slash_vfx_origin"), &BarbarianBasicAttack::set_slash_vfx_origin);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "slash_vfx_origin", PROPERTY_HINT_NODE_TYPE, Node3D::get_class_static()), "set_slash_vfx_origin", "get_slash_vfx_origin");

    ::ClassDB::bind_method(D_METHOD("get_attack_sound"), &BarbarianBasicAttack::get_attack_sound);
    ::ClassDB::bind_method(D_METHOD("set_attack_sound"), &BarbarianBasicAttack::set_attack_sound);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attack_sound", PROPERTY_HINT_RESOURCE_TYPE, AudioStream::get_class_static()), "set_attack_sound", "get_attack_sound");
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

    ERR_FAIL_NULL(use_context->get_user());
    ERR_FAIL_NULL(use_context->get_user()->get_gamelevel());

    List<HitboxComponent *> hitboxes = hitbox->get_overlapping_hitboxes();

    for(HitboxComponent *detected_hitbox : hitboxes) {
        Entity *ent = detected_hitbox->get_owning_entity();
        ERR_CONTINUE(!ent);

        if(ent == use_context->get_user()) continue; // Prevent hitting yourself
        if(!use_context->get_user()->get_gamelevel()->get_gamemode()->is_entity_enemy_of(use_context->get_user(), ent)) return; // Prevent hitting allies

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
    play_vfx_at_position(hit_visual_effect, entity->get_global_position());
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

    play_sound(action_context, attack_sound);
    play_animation(action_context, "Attack01");

    // Spawn slash VFX
    if(attack_area_vfx.is_null()) return;
    Node3D *attack_area_vfx_instance = Object::cast_to<Node3D>(attack_area_vfx->instantiate());
    if(attack_area_vfx_instance) {
        // Make it disappear when attack finishes
        Timer *timer = memnew(Timer);
        timer->set_wait_time(0.5);
        timer->set_autostart(true);
        timer->connect("timeout", callable_mp((Node *)attack_area_vfx_instance, &Node::queue_free));

        attack_area_vfx_instance->add_child(timer);

        add_child(attack_area_vfx_instance);

        // Make VFX cover entire attack area - scale if by range parameter?
        attack_area_vfx_instance->set_global_position(slash_vfx_origin ? slash_vfx_origin->get_global_position() : Vector3());
    }
}

void BarbarianBasicAttack::_prepare_attack(const Ref<ActionContext>& action_context) {
    
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

void BarbarianBasicAttack::set_range(float new_range) {
    range = new_range;
}

float BarbarianBasicAttack::get_range() {
    return range;
}

void BarbarianBasicAttack::set_slash_vfx_origin(Node3D *new_slash_vfx_origin) {
    slash_vfx_origin = new_slash_vfx_origin;
}

Node3D *BarbarianBasicAttack::get_slash_vfx_origin() {
    return slash_vfx_origin;
}

void BarbarianBasicAttack::set_attack_sound(const Ref<AudioStream> &new_attack_sound) {
    attack_sound = new_attack_sound;
}

Ref<AudioStream> BarbarianBasicAttack::get_attack_sound() {
    return attack_sound;
}