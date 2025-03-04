#include "status_effect.hpp"
#include <shared/entities/entity.h>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>

#define GDVIRTUAL_CALL_MODULE(m_name, ...)    \
    if (GDVIRTUAL_IS_OVERRIDDEN(m_name)) {      \
        GDVIRTUAL_CALL(m_name, __VA_ARGS__);    \
    } else {                                    \
        m_name(__VA_ARGS__);                    \
    }

StatusEffect::operator String() const
{
    String str = "{\n"
    "   name : %\n"
    "   max_stacks : %\n"
    "   max_duration : %\n"
    "}";
    Array format_data;
    format_data.append(get_name());
    format_data.append(max_stacks);
    format_data.append(max_duration);
    return str.format(format_data, "%");
}

StatusEffectVictimComponent *StatusEffect::get_victim_component() {
    return (StatusEffectVictimComponent *)(get_parent());
}

void StatusEffect::add_stacks() {
    bool refresh = false;
    if (current_stacks < max_stacks) {
        current_stacks++;
    }

    if (refresh) {
        current_duration = 0;
    }
}

int StatusEffect::get_current_stacks() {
    return current_stacks;
}

void StatusEffect::set_current_stacks(int stacks) {
    current_stacks = stacks;
}

int StatusEffect::get_max_stacks() {
    return max_stacks;
}

void StatusEffect::set_max_stacks(int p_stacks) {
    max_stacks = p_stacks;
}

bool StatusEffect::is_permament() {
    return permament;
}

void StatusEffect::set_permament(bool p_permament) {
    permament = p_permament;
}

void StatusEffect::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
	switch (p_notification) {
        case NOTIFICATION_POSTINITIALIZE:
            set_physics_process(true);
            break;

		case NOTIFICATION_ENTER_TREE:
            _on_apply_internal();
			break;

		case NOTIFICATION_EXIT_TREE:
            GDVIRTUAL_CALL_MODULE(_on_remove);
			break;

		case NOTIFICATION_PHYSICS_PROCESS:
            GDVIRTUAL_CALL_MODULE(_tick_internal);
            GDVIRTUAL_CALL_MODULE(_tick);
            break;
		default:
			break;
	}
}

void StatusEffect::_on_remove() {

}

void StatusEffect::_on_apply() {

}

void StatusEffect::_tick() {

}

void StatusEffect::_tick_internal() {
    // Permament effect - should not expire itself
    if(is_permament()) return;

    float delta = get_physics_process_delta_time();

    // Control effect expiration
    if(current_duration > 0) {
        // Keep it and reduce duration
        current_duration = current_duration - delta;
    }
    else {
        expire();
    }
}

void StatusEffect::expire() {
    // Disable ticking of this status effect
    set_physics_process(false);
    queue_free();
}

String StatusEffect::get_displayed_name() {
    return displayed_name;
}

void StatusEffect::set_displayed_name(const String& p_name) {
    displayed_name = p_name;
}

String StatusEffect::get_displayed_description() {
    return displayed_description;
}

void StatusEffect::set_displayed_description(const String& p_description) {
    displayed_description = p_description;
}

Ref<Texture2D> StatusEffect::get_icon() {
    return icon;
}

void StatusEffect::set_icon(const Ref<Texture2D>& p_icon) {
    icon = p_icon;
}


void StatusEffect::_bind_methods() {
    ClassDB::bind_method(D_METHOD("expire"), &StatusEffect::expire);
    ClassDB::bind_method(D_METHOD("add_stacks", "p_stacks", "p_should_refresh"), &StatusEffect::add_stacks);
    ClassDB::bind_method(D_METHOD("refresh"), &StatusEffect::refresh);

    ClassDB::bind_method(D_METHOD("get_current_stacks"), &StatusEffect::get_current_stacks);
    ClassDB::bind_method(D_METHOD("set_current_stacks", "p_stacks"), &StatusEffect::set_current_stacks);
    ClassDB::bind_method(D_METHOD("get_max_stacks"), &StatusEffect::get_max_stacks);
    ClassDB::bind_method(D_METHOD("set_max_stacks", "p_stacks"), &StatusEffect::set_max_stacks);
    ClassDB::bind_method(D_METHOD("is_permament"), &StatusEffect::is_permament);
    ClassDB::bind_method(D_METHOD("set_permament", "p_bool"), &StatusEffect::set_permament);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_stacks"), "set_max_stacks", "get_max_stacks");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_stacks"), "set_max_stacks", "get_max_stacks");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "permament"), "set_permament", "is_permament");

    ClassDB::bind_method(D_METHOD("get_displayed_name"), &StatusEffect::get_displayed_name);
    ClassDB::bind_method(D_METHOD("set_displayed_name"), &StatusEffect::set_displayed_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_name"), "set_displayed_name", "get_displayed_name");
    
    ClassDB::bind_method(D_METHOD("get_displayed_description"), &StatusEffect::get_displayed_description);
    ClassDB::bind_method(D_METHOD("set_displayed_description"), &StatusEffect::set_displayed_description);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_description"), "set_displayed_description", "get_displayed_description");

    ClassDB::bind_method(D_METHOD("get_icon"), &StatusEffect::get_icon);
    ClassDB::bind_method(D_METHOD("set_icon"), &StatusEffect::set_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, Texture::get_class_static()), "set_icon", "get_icon");

    ClassDB::bind_method(D_METHOD("get_type"), &StatusEffect::get_type);
    ClassDB::bind_method(D_METHOD("set_type"), &StatusEffect::set_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "new_type", PROPERTY_HINT_ENUM, "Misc,Buff,Debuff"), "set_type", "get_type");

    ClassDB::bind_method(D_METHOD("get_max_duration"), &StatusEffect::get_max_duration);
    ClassDB::bind_method(D_METHOD("set_max_duration"), &StatusEffect::set_max_duration);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "new_max_duration"), "set_max_duration", "get_max_duration");
}

void StatusEffect::refresh() {
    current_duration = max_duration;
}

Entity *StatusEffect::get_victim_entity() {
    return Object::cast_to<Entity>(get_node_or_null(NodePath("../..")));
}

void StatusEffect::set_inflictor(Entity *new_inflictor) {
    inflictor = new_inflictor;
}

Entity *StatusEffect::get_inflictor() {
    return inflictor;
}

void StatusEffect::set_type(StatusEffect::Type new_type) {
    type = new_type;
}

StatusEffect::Type StatusEffect::get_type() {
    return type;
}

float StatusEffect::get_max_duration() {
    return max_duration;
}

void StatusEffect::set_max_duration(float new_max_duration) {
    max_duration = new_max_duration;
}

void StatusEffect::_on_apply_internal() {
    current_duration = max_duration;

    _on_apply();
}