#include "ability_tooltip.h"
#include <shared/abilities/ability.hpp>

#include <shared/helper_macros.h>

void AbilityTooltip::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_ability_icon_display"), &AbilityTooltip::get_ability_icon_display);
    ClassDB::bind_method(D_METHOD("set_ability_icon_display", "ability_icon_display"), &AbilityTooltip::set_ability_icon_display);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ability_icon_display", PROPERTY_HINT_NODE_TYPE, TextureRect::get_class_static()), "set_ability_icon_display", "get_ability_icon_display");

    ClassDB::bind_method(D_METHOD("get_ability_name_display"), &AbilityTooltip::get_ability_name_display);
    ClassDB::bind_method(D_METHOD("set_ability_name_display", "ability_name_display"), &AbilityTooltip::set_ability_name_display);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ability_name_display", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_ability_name_display", "get_ability_name_display");
    
    ClassDB::bind_method(D_METHOD("get_ability_description_display"), &AbilityTooltip::get_ability_description_display);
    ClassDB::bind_method(D_METHOD("set_ability_description_display", "ability_description_display"), &AbilityTooltip::set_ability_description_display);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ability_description_display", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_ability_description_display", "get_ability_description_display");
}

void AbilityTooltip::set_ability(Ability *new_ability) {
    ability = new_ability;
    DISABLE_IN_EDITOR();
    _on_ability_change(new_ability);
}

Ability *AbilityTooltip::get_ability() {
    return ability;
}

void AbilityTooltip::_on_ability_change(Ability *new_ability) {
    ERR_FAIL_NULL(new_ability);
    ERR_FAIL_NULL(ability_icon_display);
    ability_icon_display->set_texture(new_ability->get_icon());

    ERR_FAIL_NULL(ability_name_display);
    ability_name_display->set_text(new_ability->get_displayed_name());
    
    ERR_FAIL_NULL(ability_description_display);
    ability_description_display->set_text(new_ability->get_displayed_description());
}

void AbilityTooltip::set_ability_icon_display(TextureRect *new_ability_icon_display) {
   ability_icon_display = new_ability_icon_display;
}

TextureRect *AbilityTooltip::get_ability_icon_display() {
    return ability_icon_display;
}

void AbilityTooltip::set_ability_name_display(Label *new_ability_name_display) {
   ability_name_display = new_ability_name_display;
}

Label *AbilityTooltip::get_ability_name_display() {
    return ability_name_display;
}

void AbilityTooltip::set_ability_description_display(Label *new_ability_description_display) {
   ability_description_display = new_ability_description_display;
}

Label *AbilityTooltip::get_ability_description_display() {
    return ability_description_display;
}
