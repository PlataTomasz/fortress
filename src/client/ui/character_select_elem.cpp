#include "character_select_elem.h"

#include <scene/gui/label.h>
#include <scene/gui/texture_button.h>

void CharacterSelectElem::_notification(int p_notification) {
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        break;

    case NOTIFICATION_DRAW:
        _draw();
        break;
    
    default:
        break;
    }
}

void CharacterSelectElem::_init() {
    
}

void CharacterSelectElem::_draw() {
    
}

void CharacterSelectElem::unhandled_input(const Ref<InputEvent> &p_event) {
	if (InputEventMouseButton *mouse_btn_event = Object::cast_to<InputEventMouseButton>(p_event.ptr())) {
		if (mouse_btn_event->is_pressed() && mouse_btn_event->get_button_index() == MouseButton::LEFT) {
            grab_focus();
		}
	}
}

void CharacterSelectElem::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_name_label"), &CharacterSelectElem::get_name_label);
    ::ClassDB::bind_method(D_METHOD("set_name_label"), &CharacterSelectElem::set_name_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "name_label", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_name_label", "get_name_label");
    ::ClassDB::bind_method(D_METHOD("get_texture_button"), &CharacterSelectElem::get_texture_button);
    ::ClassDB::bind_method(D_METHOD("set_texture_button"), &CharacterSelectElem::set_texture_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture_button", PROPERTY_HINT_NODE_TYPE, TextureButton::get_class_static()), "set_texture_button", "get_texture_button");
}

void CharacterSelectElem::set_icon(const Ref<Texture2D>& p_icon) {
    ERR_FAIL_NULL(texture_button);
    texture_button->set_texture_normal(p_icon);
}

void CharacterSelectElem::set_displayed_name(const String& p_name) {
    ERR_FAIL_NULL(name_label);
    name_label->set_text(p_name);
}


Label *CharacterSelectElem::get_name_label() {
    return name_label;
}

void CharacterSelectElem::set_name_label(Label *p_name_label) {
    name_label = p_name_label;
}

TextureButton *CharacterSelectElem::get_texture_button() {
    return texture_button;
}

void CharacterSelectElem::set_texture_button(TextureButton *p_texture_button) {
    texture_button = p_texture_button;
}

String CharacterSelectElem::get_mercenary_identifier() {
    return mercenary_identifier;
}

void CharacterSelectElem::set_mercenary_identifier(const String& p_identifier) {
    mercenary_identifier = p_identifier;
}
