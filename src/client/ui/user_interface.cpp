#include "user_interface.h"

#include <scene/resources/packed_scene.h>
#include <scene/gui/label.h>
#include <scene/gui/texture_rect.h>

#include <client/client.hpp>
#include <client/game.h>
#include <client/ui/character_select_elem.h>
#include <shared/registries/mercenary_registry.h>
#include "main_menu.h"

void UserInterface::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			break;

		default:
			break;
	}
}

void UserInterface::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_main_menu"), &UserInterface::get_main_menu);
    ::ClassDB::bind_method(D_METHOD("set_main_menu"), &UserInterface::set_main_menu);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "main_menu", PROPERTY_HINT_NODE_TYPE, MainMenu::get_class_static()), "set_main_menu", "get_main_menu");

    ADD_SIGNAL(MethodInfo("join_btn_pressed"));
}

void UserInterface::_ready() {

}

MainMenu *UserInterface::get_main_menu() {
    return main_menu;
}

void UserInterface::set_main_menu(MainMenu *p_main_menu) {
    main_menu = p_main_menu;
}

void UserInterface::show_defeat_screen() {
    ERR_FAIL_NULL(defeat_screen);
    defeat_screen->set_visible(true);
}

void UserInterface::show_victory_screen() {
    ERR_FAIL_NULL(victory_screen);
    victory_screen->set_visible(true);
}