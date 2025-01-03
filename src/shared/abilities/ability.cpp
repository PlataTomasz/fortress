#include "ability.hpp"
#include <scene/main/timer.h>

#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/entities/components/movement/movement_component.h>
#include <shared/entities/components/audio/audio_component.h>
#include <shared/entities/components/visual/visual_component_3d.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/core/game_level.h>

#ifdef SERVER
void Ability::use(const Ref<ActionContext>& action_context)
{
    if(can_be_used(action_context))
    {
        _handle_look_at(action_context);
        emit_signal("use_started");
        start_ability_cooldown(action_context);
        //Ability cast
        if(_use_time > 0) {
            _deferred_use(action_context);
        } else {
            _instant_use(action_context);
        }
    } else {
        print_line(get_current_cooldown());
        print_error("Ability instance" + Variant(this).operator String() + "is on cooldown! Remaining: " + get_current_cooldown() + " seconds");
    }
}
#endif

void Ability::_notification(int p_notification) {
	switch (p_notification) {
        case NOTIFICATION_POSTINITIALIZE:
            _init();
            break;
		default:
			break;
	}
}

#ifdef CLIENT
void Ability::use(const Ref<ActionContext>& action_context) {
    //TODO: Show indicator first if needed
    // Call RPC to server on client builds
    //rpc("ability_use_request", action_context);
    start_ability_cooldown(action_context);
    _use(action_context);
}
#endif

void Ability::start_ability_cooldown(const Ref<ActionContext> &action_context) {
    cooldown_timer->start();
}

bool Ability::can_be_used(const Ref<ActionContext>& action_context) {
    if(is_on_cooldown()) return false;

    if(action_context->get_user()) {
        DamageableComponent *damageable = action_context->get_user()->get_damageable_component();
        if(damageable) {
            if(damageable->is_dead() && !is_useable_while_dead()) {
                return false;
            }
        }
    }

    return true;
}

float Ability::get_current_cooldown()
{
    if (cooldown_timer) {
        return cooldown_timer->get_time_left();
	} else {
        return 0;
	}
}

void Ability::set_current_cooldown(float new_cooldown) {
    // Restart underlying timer with new value
    cooldown_timer->stop();
    float old_timer_wait_time = cooldown_timer->get_wait_time();
    cooldown_timer->set_wait_time(new_cooldown);
    cooldown_timer->start();
    cooldown_timer->set_wait_time(old_timer_wait_time);
}

float Ability::get_max_cooldown() {
    return max_cooldown;
}

void Ability::set_max_cooldown(float new_cooldown) {
    max_cooldown = new_cooldown;

    if(cooldown_timer) {
        cooldown_timer->set_wait_time(new_cooldown);
    }
    //Emit signal that cooldown changed?
}

bool Ability::is_on_cooldown()
{
    return get_current_cooldown() > 0;
}

void Ability::_before_ability_use(const Ref<ActionContext>& action_context) {

}

Ability::LookAtBehaviour *Ability::_get_where_to_look_behaviour() {
	switch (where_to_look_at) {
		case KEEP_CURRENT: {
			return &_unchanged_look_at_behaviour;
		} break;
		case AT_TARGET_ENTITY: {
			return &_at_target_entity_look_at_behaviour;
		} break;
		case AT_TARGET_POSITION: {
			return &_at_target_position_look_at_behaviour;
		} break;
		default: {
			return &_unchanged_look_at_behaviour;
		} break;
	}
}

void Ability::_init() {
    cooldown_timer = memnew(Timer);
    cooldown_timer->set_one_shot(true);
    add_child(cooldown_timer);
}

Ref<Texture2D> Ability::get_icon() {
    return icon;
}

void Ability::set_icon(const Ref<Texture2D> &new_icon) {
    icon = new_icon;
}

String Ability::get_displayed_description() {
    return displayed_description;
}

void Ability::set_displayed_description(const String &new_description) {
    displayed_description = new_description;
}

String Ability::get_displayed_name() {
    return displayed_name;
}

void Ability::set_displayed_name(const String &new_name) {
    displayed_name = new_name;
}


Ability::Ability()
{
    
}

void Ability::_bind_methods() {
    ADD_SIGNAL(MethodInfo("use_started"));
    ADD_SIGNAL(MethodInfo("use_finished"));

    ClassDB::bind_method(D_METHOD("use", "action_context"), &Ability::use);

    ClassDB::bind_method(D_METHOD("set_displayed_description", "new_description"), &Ability::set_displayed_description);
    ClassDB::bind_method(D_METHOD("get_displayed_description"), &Ability::get_displayed_description);
    
    ClassDB::bind_method(D_METHOD("set_displayed_name", "new_name"), &Ability::set_displayed_name);
    ClassDB::bind_method(D_METHOD("get_displayed_name"), &Ability::get_displayed_name);

    ClassDB::bind_method(D_METHOD("set_icon", "new_icon"), &Ability::set_icon);
    ClassDB::bind_method(D_METHOD("get_icon"), &Ability::get_icon);



    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_name"), "set_displayed_name", "get_displayed_name");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_description", PROPERTY_HINT_MULTILINE_TEXT), "set_displayed_description", "get_displayed_description");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_icon", "get_icon");

    ClassDB::bind_method(D_METHOD("set_max_cooldown", "new_icon"), &Ability::set_max_cooldown);
    ClassDB::bind_method(D_METHOD("get_max_cooldown"), &Ability::get_max_cooldown);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_cooldown"), "set_max_cooldown", "get_max_cooldown");

    ClassDB::bind_method(D_METHOD("set_current_cooldown", "new_icon"), &Ability::set_current_cooldown);
    ClassDB::bind_method(D_METHOD("get_current_cooldown"), &Ability::get_current_cooldown);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "current_cooldown"), "set_current_cooldown", "get_current_cooldown");

    ClassDB::bind_method(D_METHOD("set_useable_while_dead", "new_icon"), &Ability::set_useable_while_dead);
    ClassDB::bind_method(D_METHOD("is_useable_while_dead"), &Ability::is_useable_while_dead);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "useable_while_dead"), "set_useable_while_dead", "is_useable_while_dead");

    ClassDB::bind_method(D_METHOD("set_where_to_look_at", "new_icon"), &Ability::set_where_to_look_at);
    ClassDB::bind_method(D_METHOD("get_where_to_look_at"), &Ability::get_where_to_look_at);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "where_to_look_at", PROPERTY_HINT_ENUM, "Keep,At position,At entity"), "set_where_to_look_at", "get_where_to_look_at");

    ClassDB::bind_method(D_METHOD("set_locks_movement", "locks_movement"), &Ability::set_locks_movement);
    ClassDB::bind_method(D_METHOD("get_locks_movement"), &Ability::is_locks_movement);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "locks_movement"), "set_locks_movement", "get_locks_movement");

    ClassDB::bind_method(D_METHOD("set_use_time", "new_icon"), &Ability::set_use_time);
    ClassDB::bind_method(D_METHOD("get_use_time"), &Ability::get_use_time);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "use_time"), "set_use_time", "get_use_time");
}

AbilityCasterComponent *Ability::get_ability_caster() {
    return Object::cast_to<AbilityCasterComponent>(get_parent());
}

void Ability::set_where_to_look_at(Ability::WhereToLookBeforeUse new_where_to_look_at) {
    where_to_look_at = new_where_to_look_at;
}
Ability::WhereToLookBeforeUse Ability::get_where_to_look_at() {
    return where_to_look_at;
}

void Ability::set_use_time(float new_use_time) {
    _use_time = new_use_time;
}

float Ability::get_use_time() {
    return _use_time;
}

void Ability::set_locks_movement(bool new_locks_movement) {
    locks_movement = new_locks_movement;
}

bool Ability::is_locks_movement() {
    return locks_movement;
}

void Ability::_handle_look_at(const Ref<ActionContext>& action_context) {
    _get_where_to_look_behaviour()->look(action_context);
}


/*
bool Ability::is_valid_target(const Ref<ActionContext>& action_context) {
    return true;
}
*/

void Ability::_deferred_use_handler(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(action_context->get_user());
    MovementComponent *movement_component = action_context->get_user()->get_movement_component();
    if(movement_component) {
        movement_component->unpause_movement(this);
    }

    // TODO: Check if ability can still be used
    _use(action_context);
    emit_signal("use_finished");
}

void Ability::_deferred_use(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(action_context->get_user());
    MovementComponent *movement_component = action_context->get_user()->get_movement_component();
    if(movement_component && locks_movement) {
        movement_component->pause_movement(this);
    }

    Timer *timer = memnew(Timer);
    timer->set_autostart(true);
    timer->set_wait_time(_use_time);
    timer->set_one_shot(true);

    // FIXME: Nothing checks that ability can no longer be used at this point - might lead to ability use after death
    timer->connect("timeout", callable_mp(this, &Ability::_deferred_use_handler).bind(action_context));

    add_child(timer);
}

void Ability::_instant_use(const Ref<ActionContext>& action_context) {
    _use(action_context);
    emit_signal("use_finished");
}

void Ability::play_sound(const Ref<ActionContext> &action_context, const Ref<AudioStream> &sound_resource) {
    ERR_FAIL_NULL(action_context->get_user());
    ERR_FAIL_NULL(action_context->get_user()->get_audio_component());

    action_context->get_user()->get_audio_component()->play_audio_stream(sound_resource);
}

void Ability::play_animation(const Ref<ActionContext> &action_context, const String &animation_name) {
    ERR_FAIL_NULL(action_context->get_user());
    ERR_FAIL_NULL_MSG(action_context->get_user()->get_visual_component(), "Failed to play animation! Missing VisualComponent3D!");

    action_context->get_user()->get_visual_component()->play_animation_override(animation_name);
}

void Ability::play_vfx(const Ref<ActionContext> &action_context, const Ref<PackedScene> &vfx_scene) {
    ERR_FAIL_NULL(vfx_scene);
    Node3D *vfx_instance = Object::cast_to<Node3D>(vfx_scene->instantiate());
    ERR_FAIL_NULL(vfx_instance);
    add_child(vfx_instance);
}

void Ability::play_vfx_at_position(const Ref<ActionContext> &action_context, const Ref<PackedScene> &vfx_scene, const Vector3 &vfx_position) {
    ERR_FAIL_NULL(vfx_scene);
    Node3D *vfx_instance = Object::cast_to<Node3D>(vfx_scene->instantiate());
    ERR_FAIL_NULL(vfx_instance);
    vfx_instance->set_position(vfx_position);
    add_child(vfx_instance);
}

void Ability::set_useable_while_dead(bool new_useable_while_dead) {
    useable_while_dead = new_useable_while_dead;
}

bool Ability::is_useable_while_dead() {
    
    return useable_while_dead;
}

void Ability::play_vfx_at_position(const Ref<PackedScene> &vfx_scene, const Vector3 &vfx_position) {
    ERR_FAIL_NULL(vfx_scene);
    Node3D *vfx_instance = Object::cast_to<Node3D>(vfx_scene->instantiate());
    ERR_FAIL_NULL(vfx_instance);

    ERR_FAIL_NULL(get_ability_caster());
    ERR_FAIL_NULL(get_ability_caster()->get_owning_entity());
    ERR_FAIL_NULL(get_ability_caster()->get_owning_entity()->get_gamelevel());
    
    GameLevel *level = get_ability_caster()->get_owning_entity()->get_gamelevel();
    if(level) {
        level->add_child(vfx_instance);
    } else {
        add_child(vfx_instance);
    }
    vfx_instance->set_global_position(vfx_position);
}