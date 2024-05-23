#include "status_effect_indicator.h"

#include <scene/resources/packed_scene.h>
#include "status_effect_tooltip.h"

#include <shared/status_effects/status_effect.hpp>

void StatusEffectIndicator::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_tooltip_object"), &StatusEffectIndicator::get_tooltip_object);
    ClassDB::bind_method(D_METHOD("set_tooltip_object"), &StatusEffectIndicator::set_tooltip_object);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tooltip_object", PROPERTY_HINT_NODE_TYPE, TextureRect::get_class_static()), "set_tooltip_object", "get_tooltip_object");
}

void StatusEffectIndicator::_notification(int p_notification) {
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        break;
    
    default:
        break;
    }
}

void StatusEffectIndicator::_init() {
	connect("mouse_entered", callable_mp(this, &StatusEffectIndicator::set_tooltip_visible).bind(true));
	connect("mouse_exited", callable_mp(this, &StatusEffectIndicator::set_tooltip_visible).bind(false));
}

void StatusEffectIndicator::set_tooltip_visible(bool p_visible) {
    tooltip_object->set_visible(p_visible);
}

bool StatusEffectIndicator::is_tooltip_visible() {
    return tooltip_object->is_visible();
}

StatusEffect *StatusEffectIndicator::get_status_effect() const {
	return status_effect;
}

void StatusEffectIndicator::set_status_effect(StatusEffect *status_effect_) {
	status_effect = status_effect_;
}