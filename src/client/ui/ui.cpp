#include "ui.h"

#include <shared/status_effects/status_effect.hpp>
#include <client/ui/status_effect_indicator.h>
#include <scene/resources/packed_scene.h>

StatusEffectIndicator *UI::create_status_effect_indicator(StatusEffect *for_status_effect) {
    Ref<PackedScene> scene = ResourceLoader::load("res://scenes/ui/status_effects/Indicator.tscn");
    if(scene.is_null()) {
        return nullptr;
    }
    else {
        StatusEffectIndicator *instance = Object::cast_to<StatusEffectIndicator>(scene->instantiate());
        instance->set_displayed_name(for_status_effect->get_displayed_name());
        instance->set_displayed_description(for_status_effect->get_displayed_description());
        instance->set_displayed_icon(for_status_effect->get_displayed_icon());
        return instance;
    }
}