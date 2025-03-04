#include "ability_button.h"

#include <shared/abilities/ability.hpp>
#include <scene/gui/texture_progress_bar.h>
#include <scene/gui/label.h>
#include <client/ui/game/abilities/ability_tooltip.h>

void ActiveAbilityButton::_init() {
    cooldown_timer = memnew(Timer);
    cooldown_timer->set_autostart(true);
    add_child(cooldown_timer);

    set_process(true);
}

void ActiveAbilityButton::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_progress_bar"), &ActiveAbilityButton::get_progress_bar);
    ClassDB::bind_method(D_METHOD("set_progress_bar", "progress_bar"), &ActiveAbilityButton::set_progress_bar);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "progress_bar", PROPERTY_HINT_NODE_TYPE, TextureProgressBar::get_class_static()), "set_progress_bar", "get_progress_bar");

    ClassDB::bind_method(D_METHOD("get_value_indicator"), &ActiveAbilityButton::get_value_indicator);
    ClassDB::bind_method(D_METHOD("set_value_indicator", "value_indicator"), &ActiveAbilityButton::set_value_indicator);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "value_indicator", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_value_indicator", "get_value_indicator");

    ClassDB::bind_method(D_METHOD("get_ability_tooltip"), &ActiveAbilityButton::get_ability_tooltip);
    ClassDB::bind_method(D_METHOD("set_ability_tooltip", "ability_tooltip"), &ActiveAbilityButton::set_ability_tooltip);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ability_tooltip", PROPERTY_HINT_NODE_TYPE, AbilityTooltip::get_class_static()), "set_ability_tooltip", "get_ability_tooltip");
}

void ActiveAbilityButton::_on_ability_change(Ability *new_ability) {
    ERR_FAIL_NULL(new_ability);

    set_indicator_icon(new_ability->get_icon());

    if(new_ability->get_max_cooldown() > 0) {
        set_indicator_max_value(new_ability->get_max_cooldown());
    }

    set_indicator_current_value(new_ability->get_current_cooldown());
    
    ERR_FAIL_NULL(ability_tooltip);
    ability_tooltip->set_ability(new_ability);
}

void ActiveAbilityButton::_process_frame() {
    if(ability) {
        if(ability->get_max_cooldown() > 0) {
            set_indicator_max_value(ability->get_max_cooldown());
        }

        set_indicator_current_value(ability->get_current_cooldown());
    }
}

void ActiveAbilityButton::set_indicator_icon(const Ref<Texture2D>& new_icon) {
    progress_bar->set_under_texture(new_icon);
}

void ActiveAbilityButton::set_indicator_max_value(float max_value) {
    progress_bar->set_max(max_value);
}

void ActiveAbilityButton::set_indicator_current_value(float current_value) {
    if(current_value == 0) {
        value_indicator->set_text("");
    } else if(current_value > 0 && current_value < 1) {
        value_indicator->set_text(vformat("%.1f", current_value));
    } else {
        value_indicator->set_text(vformat("%.f", current_value));
    }

    progress_bar->set_value(current_value);
}

void ActiveAbilityButton::set_progress_bar(TextureProgressBar *new_progress_bar) {
    progress_bar = new_progress_bar;
}

TextureProgressBar *ActiveAbilityButton::get_progress_bar() {
    return progress_bar;
}

void ActiveAbilityButton::set_value_indicator(Label *new_value_indicator) {
    value_indicator = new_value_indicator;
}

Label *ActiveAbilityButton::get_value_indicator() {
    return value_indicator;
}

void ActiveAbilityButton::set_ability(Ability *new_ability) {
    ability = new_ability;
    DISABLE_IN_EDITOR();
    _on_ability_change(new_ability);
}

Ability *ActiveAbilityButton::get_ability() {
    return ability;
}

void ActiveAbilityButton::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_PROCESS: {
			_process_frame();
		} break;

        case NOTIFICATION_POSTINITIALIZE: {
            _init();
        } break;

		default:
			break;
	}
}

void ActiveAbilityButton::_on_mouse_entered() {
    ERR_FAIL_NULL(ability_tooltip);
    ability_tooltip->set_visible(true);
}

void ActiveAbilityButton::_on_mouse_exited() {
    ERR_FAIL_NULL(ability_tooltip);
    ability_tooltip->set_visible(false);
}
 
void ActiveAbilityButton::set_ability_tooltip(AbilityTooltip *new_ability_tooltip) {
    ability_tooltip = new_ability_tooltip;
    DISABLE_IN_EDITOR();
    _reconnect_tooltip_signals(new_ability_tooltip);
}

AbilityTooltip *ActiveAbilityButton::get_ability_tooltip() {
    return ability_tooltip;
}

void ActiveAbilityButton::_reconnect_tooltip_signals(AbilityTooltip *new_ability_tooltip) {
    if(ability) 
        new_ability_tooltip->set_ability(ability);

    connect("mouse_entered", callable_mp(this, &ActiveAbilityButton::_on_mouse_entered));
    connect("mouse_exited", callable_mp(this, &ActiveAbilityButton::_on_mouse_exited));
}