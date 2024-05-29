#include "main_menu.h"

#include "character_select_elem.h"
#include <scene/gui/line_edit.h>

#include <scene/gui/texture_button.h>
#include <shared/registries/mercenary_registry.h>

void MainMenu::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_ip_input"), &MainMenu::get_ip_input);
    ClassDB::bind_method(D_METHOD("set_ip_input", "ip_input"), &MainMenu::set_ip_input);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ip_input", PROPERTY_HINT_NODE_TYPE, LineEdit::get_class_static()), "set_ip_input", "get_ip_input");

    ClassDB::bind_method(D_METHOD("get_nickname_input"), &MainMenu::get_nickname_input);
    ClassDB::bind_method(D_METHOD("set_nickname_input", "nickname_input"), &MainMenu::set_nickname_input);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "nickname_input", PROPERTY_HINT_NODE_TYPE, LineEdit::get_class_static()), "set_nickname_input", "get_nickname_input");

    ClassDB::bind_method(D_METHOD("get_join_button"), &MainMenu::get_join_button);
    ClassDB::bind_method(D_METHOD("set_join_button", "join_button"), &MainMenu::set_join_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "join_button", PROPERTY_HINT_NODE_TYPE, BaseButton::get_class_static()), "set_join_button", "get_join_button");

    ClassDB::bind_method(D_METHOD("get_character_button_group"), &MainMenu::get_character_button_group);
    ClassDB::bind_method(D_METHOD("set_character_button_group", "character_button_group"), &MainMenu::set_character_button_group);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "character_button_group", PROPERTY_HINT_RESOURCE_TYPE, ButtonGroup::get_class_static()), "set_character_button_group", "get_character_button_group");

    ClassDB::bind_method(D_METHOD("get_character_select_area"), &MainMenu::get_character_select_area);
    ClassDB::bind_method(D_METHOD("set_character_select_area", "character_select_area"), &MainMenu::set_character_select_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "character_select_area", PROPERTY_HINT_NODE_TYPE, Control::get_class_static()), "set_character_select_area", "get_character_select_area");
}

String MainMenu::get_choosen_nickname() {
    ERR_FAIL_NULL_V(nickname_input, String());
    return nickname_input->get_text();
}

void MainMenu::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE: {
			character_button_group = Ref<ButtonGroup>(memnew(ButtonGroup));
			character_button_group->set_local_to_scene(false);
		} break;
		case NOTIFICATION_READY: {
            Ref<PackedScene> char_select_elem_scene = ResourceLoader::load("res://scenes/ui/CharacterListElement.tscn");

            // TODO: Display Icons before joining a server
            PackedStringArray mercenary_names = MercenaryRegistry::get_singleton()->get_registered_names();
            for(const String &name : mercenary_names) {
                // Create character selection entry for mercenary
                CharacterSelectElem *element = static_cast<CharacterSelectElem *>(char_select_elem_scene->instantiate());
                // Currently they are the same, but will not be when I'll involve translations
                element->set_displayed_name(name);
                element->set_mercenary_identifier(name);
                element->get_texture_button()->set_button_group(character_button_group);

                character_select_area->add_child(element);
                
            }
		} break;

		default:
			break;
	}
}

Control *MainMenu::get_character_select_area() {
    return character_select_area;
}

void MainMenu::set_character_select_area(Control *p_character_select_area) {
    character_select_area = p_character_select_area;
}

String MainMenu::get_server_adress() {
    ERR_FAIL_NULL_V(ip_input, String());
    return ip_input->get_text();
}

String MainMenu::get_selected_mercenary() {
    BaseButton *selected_btn = character_button_group->get_pressed_button();
    CharacterSelectElem *elem = static_cast< CharacterSelectElem *>(selected_btn->get_owner());
    if (elem) {
        return elem->get_mercenary_identifier();
    } else {
        return String();
    }
}

Ref<ButtonGroup> MainMenu::get_character_button_group() {
    return character_button_group;
}

void MainMenu::set_character_button_group(const Ref<ButtonGroup> &p_button_group) {
    character_button_group = p_button_group;
}

BaseButton *MainMenu::get_join_button() {
    return join_button;
}

void MainMenu::set_join_button(BaseButton *p_join_button) {
    join_button = p_join_button;
}


LineEdit *MainMenu::get_nickname_input() {
    return nickname_input;
}

void MainMenu::set_nickname_input(LineEdit *p_nickname_input) {
    nickname_input = p_nickname_input;
}

LineEdit *MainMenu::get_ip_input() {
    return ip_input;
}

void MainMenu::set_ip_input(LineEdit *p_ip_input) {
    ip_input = p_ip_input;
}

int MainMenu::get_server_port() {
    // TODO: Implement properly
    return 7654;
}