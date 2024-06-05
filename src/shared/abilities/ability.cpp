#include "ability.hpp"
#include <scene/main/timer.h>

#ifdef SERVER
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
        case NOTIFICATION_POSTINITIALIZE:
            _init();
            break;
		default:
			break;
	}
}
#endif

#ifdef CLIENT
Ability::AbilityUseError Ability::use(const Ref<ActionContext>& action_context) {
    //TODO: Show indicator first if needed
    // Call RPC to server on client builds
    rpc("ability_use_request", action_context);
    print_line("Display name: ", displayed_name);
    return Ability::AbilityUseError::SUCCESS;
}
#endif

float Ability::get_current_cooldown()
{
    if (cooldown_timer) {
        return cooldown_timer->get_time_left();
	} else {
        return 0;
	}
}

float Ability::get_max_cooldown() {
    return max_cooldown;
}

void Ability::set_max_cooldown(float new_cooldown) {
    max_cooldown = new_cooldown;
    cooldown_timer->set_wait_time(max_cooldown);
    //Emit signal that cooldown changed?
}

bool Ability::is_on_cooldown()
{
    return get_current_cooldown() > 0;
}

void Ability::_init() {
    cooldown_timer = memnew(Timer);
}

Ability::AbilityUseError Ability::use_check(const Ref<ActionContext>& action_context)
{
    if(is_on_cooldown()) {
        return Ability::AbilityUseError::ABILITY_ON_COOLDOWN;
    } else {
        return Ability::AbilityUseError::SUCCESS;
    }
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

    ClassDB::bind_method(D_METHOD("set_displayed_description", "new_description"), &Ability::set_displayed_description);
    ClassDB::bind_method(D_METHOD("get_displayed_description"), &Ability::get_displayed_description);
    
    ClassDB::bind_method(D_METHOD("set_displayed_name", "new_name"), &Ability::set_displayed_name);
    ClassDB::bind_method(D_METHOD("get_displayed_name"), &Ability::get_displayed_name);

    ClassDB::bind_method(D_METHOD("set_icon", "new_icon"), &Ability::set_icon);
    ClassDB::bind_method(D_METHOD("get_icon"), &Ability::get_icon);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_name"), "set_displayed_name", "get_displayed_name");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_description", PROPERTY_HINT_MULTILINE_TEXT), "set_displayed_description", "get_displayed_description");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_icon", "get_icon");

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "cooldown_timer_path"), "set_cooldown_timer_path", "get_cooldown_timer_path");
}

/*
bool Ability::is_valid_target(const Ref<ActionContext>& action_context) {
    return true;
}
*/