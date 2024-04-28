#include "ability.hpp"
#include <scene/main/timer.h>

float Ability::get_current_cooldown()
{
    if (cooldown_timer) {
        return cooldown_timer->get_time_left();
	} else {
        return 0;
	}
}

float Ability::get_max_cooldown()
{
	if (cooldown_timer) {
        return cooldown_timer->get_wait_time();
	} else {
        return 0;
	}
}

bool Ability::is_on_cooldown()
{
    return get_current_cooldown() > 0;
}

Ability::AbilityUseError Ability::use(const Ref<ActionContext>& action_context)
{
    Ability::AbilityUseError result = use_check(action_context);
    if(result == Ability::AbilityUseError::SUCCESS)
    {
        //Ability cast 
        _use(action_context);
        cooldown_timer->start();
    } else {
        print_error("Ability instance" + Variant(this).operator String() + "couldn't be used!");
    }
    return result;
}

void Ability::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			break;
		default:
			break;
	}
}

void Ability::_ready() {
    cooldown_timer = Object::cast_to<Timer>(get_node_or_null(cooldown_timer_path));
}

Entity *Ability::get_owner()
{
    return static_cast<Entity *>(get_parent());
}

void Ability::force_use(const Ref<ActionContext>& action_context)
{
    
}

Ability::AbilityUseError Ability::use_check(const Ref<ActionContext>& action_context)
{
    if(is_on_cooldown()) {
        return Ability::AbilityUseError::ABILITY_ON_COOLDOWN;
    } else {
        return Ability::AbilityUseError::SUCCESS;
    }
}

NodePath Ability::get_cooldown_timer_path() {
    return cooldown_timer_path;
}

void Ability::set_cooldown_timer_path(const NodePath& p_cooldown_timer_path) {
    cooldown_timer_path = p_cooldown_timer_path;
}

Timer *Ability::get_cooldown_timer() {
    return cooldown_timer;
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
    ClassDB::bind_method(D_METHOD("use", "action_context"), &Ability::use);
    ClassDB::bind_method(D_METHOD("use_check", "action_context"), &Ability::use_check);

    ClassDB::bind_method(D_METHOD("set_cooldown_timer_path", "p_cooldown_timer_path"), &Ability::set_cooldown_timer_path);
    ClassDB::bind_method(D_METHOD("get_cooldown_timer_path"), &Ability::get_cooldown_timer_path);

    ClassDB::bind_method(D_METHOD("set_displayed_description", "new_description"), &Ability::set_displayed_description);
    ClassDB::bind_method(D_METHOD("get_displayed_description"), &Ability::get_displayed_description);
    
    ClassDB::bind_method(D_METHOD("set_displayed_name", "new_name"), &Ability::set_displayed_name);
    ClassDB::bind_method(D_METHOD("set_displayed_name"), &Ability::get_displayed_name);

    ClassDB::bind_method(D_METHOD("set_icon", "new_icon"), &Ability::set_icon);
    ClassDB::bind_method(D_METHOD("get_icon"), &Ability::get_icon);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_name"), "set_displayed_name", "get_displayed_name");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_description"), "set_displayed_description", "get_displayed_description");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon"), "set_icon", "get_icon");

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "cooldown_timer_path"), "set_cooldown_timer_path", "get_cooldown_timer_path");
}