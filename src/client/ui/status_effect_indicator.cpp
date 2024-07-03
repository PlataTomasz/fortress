#include "status_effect_indicator.h"

#include <scene/resources/packed_scene.h>
#include <client/ui/game/status_effect_tooltip.h>

#include <shared/status_effects/status_effect.hpp>

#include <shared/helper_macros.h>
#include <shared/entities/traits/traits.h>
#include <scene/gui/texture_rect.h>
#include <shared/registries/mercenary_registry.h>

void StatusEffectIndicator::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_tooltip_object"), &StatusEffectIndicator::get_tooltip_object);
    ClassDB::bind_method(D_METHOD("set_tooltip_object"), &StatusEffectIndicator::set_tooltip_object);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tooltip_object", PROPERTY_HINT_NODE_TYPE, StatusEffectTooltip::get_class_static()), "set_tooltip_object", "get_tooltip_object");

    ClassDB::bind_method(D_METHOD("get_icon_display"), &StatusEffectIndicator::get_icon_display);
    ClassDB::bind_method(D_METHOD("set_icon_display"), &StatusEffectIndicator::set_icon_display);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon_display", PROPERTY_HINT_NODE_TYPE, TextureRect::get_class_static()), "set_icon_display", "get_icon_display");
}

void StatusEffectIndicator::initialize(StatusEffect *p_status_effect) {
    set_status_effect(p_status_effect);
    tooltip_object->set_displayed_name(p_status_effect->get_displayed_name());
    tooltip_object->set_displayed_description(p_status_effect->get_displayed_description());
    set_icon(p_status_effect->get_icon());
}

void StatusEffectIndicator::set_icon(const Ref<Texture2D>& p_icon) {
    icon_display->set_texture(p_icon);
}

TextureRect *StatusEffectIndicator::get_icon_display() {
    return icon_display;
}

void StatusEffectIndicator::set_icon_display(TextureRect *p_icon_display) {
    icon_display = p_icon_display;
}

StatusEffectTooltip *StatusEffectIndicator::get_tooltip_object() {
    return tooltip_object;
}

void StatusEffectIndicator::set_tooltip_object(StatusEffectTooltip *p_tooltip) {
    tooltip_object = p_tooltip;
}

void StatusEffectIndicator::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        break;
    case NOTIFICATION_READY:
    {
        // Toggle visibility when mouse enters and leaves
        connect("mouse_entered", callable_mp(this, &StatusEffectIndicator::_change_tooltip_visibility).bind(true));
	    connect("mouse_exited", callable_mp(this, &StatusEffectIndicator::_change_tooltip_visibility).bind(false));
        print_line(Registry<Mercenary>::get_singleton()->get_registered_names());
    }
        break;
    
    default:
        break;
    }
}

void StatusEffectIndicator::_init() {

}

StatusEffect *StatusEffectIndicator::get_status_effect() const {
	return status_effect;
}

void StatusEffectIndicator::set_status_effect(StatusEffect *status_effect_) {
	status_effect = status_effect_;
}

void StatusEffectIndicator::_change_tooltip_visibility(bool p_visibility) {
    if(tooltip_enabled) {
        ERR_FAIL_NULL(tooltip_object);
        tooltip_object->set_visible(p_visibility);
    }
}