#include "character_select_elem.h"

#include <scene/gui/label.h>
#include <scene/gui/texture_button.h>

#include <shared/helper_macros.h>
#include <scene/gui/texture_rect.h>

void CharacterSelectElem::_notification(int p_notification) {
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        print_line("Initialized " + this->to_string());
        break;

    case NOTIFICATION_DRAW:
        _draw();
        break;

    case NOTIFICATION_PARENTED:
        print_line(this->to_string() + " parented to " + get_parent()->to_string());
        break;
    
    default:
        break;
    }
}

void CharacterSelectElem::set_title(const String& new_title) {
    title = new_title;
    DISABLE_IN_EDITOR();
    ERR_FAIL_NULL(name_label);
    name_label->set_text(title);
}

String CharacterSelectElem::get_title() {
    return title;
}

void CharacterSelectElem::set_character_index(const String& new_character_index) {
    character_index = new_character_index;
}

String CharacterSelectElem::get_character_index() {
    return character_index;
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
    ::ClassDB::bind_method(D_METHOD("get_mercenary_icon_quad"), &CharacterSelectElem::get_mercenary_icon_quad);
    ::ClassDB::bind_method(D_METHOD("set_mercenary_icon_quad"), &CharacterSelectElem::set_mercenary_icon_quad);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mercenary_icon_quad", PROPERTY_HINT_NODE_TYPE, TextureRect::get_class_static()), "set_mercenary_icon_quad", "get_mercenary_icon_quad");
    ::ClassDB::bind_method(D_METHOD("get_name_label"), &CharacterSelectElem::get_name_label);
    ::ClassDB::bind_method(D_METHOD("set_name_label"), &CharacterSelectElem::set_name_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "name_label", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_name_label", "get_name_label");
    ::ClassDB::bind_method(D_METHOD("get_character_index"), &CharacterSelectElem::get_character_index);
    ::ClassDB::bind_method(D_METHOD("set_character_index"), &CharacterSelectElem::set_character_index);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "character_index"), "set_character_index", "get_character_index");
    ::ClassDB::bind_method(D_METHOD("get_title"), &CharacterSelectElem::get_title);
    ::ClassDB::bind_method(D_METHOD("set_title"), &CharacterSelectElem::set_title);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");
    ::ClassDB::bind_method(D_METHOD("get_icon"), &CharacterSelectElem::get_icon);
    ::ClassDB::bind_method(D_METHOD("set_icon"), &CharacterSelectElem::set_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, Texture2D::get_class_static()), "set_icon", "get_icon");
}

void CharacterSelectElem::set_mercenary_icon_quad(TextureRect *new_mercenary_icon_quad) {
    mercenary_icon_quad = new_mercenary_icon_quad;
}

TextureRect *CharacterSelectElem::get_mercenary_icon_quad() {
    return mercenary_icon_quad;
}


void CharacterSelectElem::set_icon(const Ref<Texture2D>& p_icon) {
    icon = p_icon;
    DISABLE_IN_EDITOR();
    ERR_FAIL_NULL(mercenary_icon_quad);
    mercenary_icon_quad->set_texture(p_icon);
}

Ref<Texture2D> CharacterSelectElem::get_icon() {
    return icon;
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
