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
            GDVIRTUAL_CALL_MODULE(_on_apply);
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

Ref<Texture2D> StatusEffect::get_displayed_icon() {
    return icon;
}

void StatusEffect::set_displayed_icon(const Ref<Texture2D>& p_icon) {
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
}

void StatusEffect::refresh() {
    current_duration = max_duration;
}

Node *StatusEffect::get_victim_entity() {
    return get_node_or_null(NodePath("../.."));
}