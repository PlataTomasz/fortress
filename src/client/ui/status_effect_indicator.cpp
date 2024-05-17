#include "status_effect_indicator.h"

#include <scene/resources/packed_scene.h>
#include "status_effect_tooltip.h"

#include <shared/status_effects/status_effect.hpp>

Control *StatusEffectIndicator::make_custom_tooltip(const String &p_text) const {
    Ref<PackedScene> custom_tooltip_scene = ResourceLoader::load("", PackedScene::get_class_static());
    ERR_FAIL_NULL_V(custom_tooltip_scene, nullptr);
    StatusEffectTooltip *custom_tooltip = Object::cast_to<StatusEffectTooltip>(custom_tooltip_scene->instantiate());
    ERR_FAIL_NULL_V(custom_tooltip, nullptr);
    
    custom_tooltip->set_displayed_name(status_effect->);
    custom_tooltip->set_displayed_description();
    custom_tooltip->set_displayed_source();

    return custom_tooltip;
}

StatusEffect *StatusEffectIndicator::get_status_effect() const {
	return status_effect;
}

void StatusEffectIndicator::set_status_effect(StatusEffect *status_effect_) {
	status_effect = status_effect_;
}