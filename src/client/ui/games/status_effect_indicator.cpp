#include "status_effect_indicator.h"

#include <scene/gui/label.h>
#include <scene/gui/texture_rect.h>

void StatusEffectIndicator::set_displayed_name(const String& name) {
    ERR_FAIL_NULL(name_label);
    name_label->set_text(name);
}

void StatusEffectIndicator::set_displayed_description(const String& description) {
    ERR_FAIL_NULL(description_label);
    description_label->set_text(description);
}

void StatusEffectIndicator::set_displayed_icon(const Ref<Texture2D>& icon) {
    ERR_FAIL_NULL(icon_display);
    icon_display->set_texture(icon);
}

Label *StatusEffectIndicator::get_name_label() {
    return name_label;
}

void StatusEffectIndicator::set_name_label(Label *p_name_label) {
    name_label = p_name_label;
}

Label *StatusEffectIndicator::get_description_label() {
    return description_label;
}

void StatusEffectIndicator::set_description_label(Label *p_description_label) {
    description_label = p_description_label;
}

TextureRect *StatusEffectIndicator::get_icon_display() {
    return icon_display;
}

void StatusEffectIndicator::set_icon_display(TextureRect *p_icon_display) {
    icon_display = p_icon_display;
}

void StatusEffectIndicator::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_description_label"), &StatusEffectIndicator::get_description_label);
    ClassDB::bind_method(D_METHOD("set_description_label"), &StatusEffectIndicator::set_description_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "description_label", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_description_label", "get_description_label");

    ClassDB::bind_method(D_METHOD("get_name_label"), &StatusEffectIndicator::get_name_label);
    ClassDB::bind_method(D_METHOD("set_name_label"), &StatusEffectIndicator::set_name_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "name_label", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_name_label", "get_name_label");

    ClassDB::bind_method(D_METHOD("get_icon_display"), &StatusEffectIndicator::get_icon_display);
    ClassDB::bind_method(D_METHOD("set_icon_display"), &StatusEffectIndicator::set_icon_display);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon_display", PROPERTY_HINT_NODE_TYPE, TextureRect::get_class_static()), "set_icon_display", "get_icon_display");

    
}