#include "user_interface.h"

#include <scene/resources/packed_scene.h>
#include <scene/gui/label.h>
#include <scene/gui/texture_rect.h>

#include <client/client.hpp>
#include <client/game.h>
#include <client/ui/character_select_elem.h>

void UserInterface::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			break;

		default:
			break;
	}
}

void UserInterface::_init() {
    set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_PASS);
    set_anchors_preset(LayoutPreset::PRESET_FULL_RECT);
    //Currently User Interface has only character and nickname selection
    Ref<PackedScene> char_select_scene = ResourceLoader::load("res://scenes/ui/CharacterSelection.tscn");
    character_selection = static_cast<Control *>(char_select_scene->instantiate());
    add_child(character_selection);

    Ref<PackedScene> char_select_elem_scene = ResourceLoader::load("res://scenes/ui/CharacterListElement.tscn");
    Control *elements = static_cast<Control *>(character_selection->get_node(NodePath("CharacterArea/MarginContainer/ScrollContainer/GridContainer")));

    //Create entry for each available character
    //TODO: Implement
    List<StringName> mercenary_classes;
    Client::get_game()->fetch_mercenary_classes(mercenary_classes);

    for(String character_name : mercenary_classes) {
        CharacterSelectElem *element = static_cast<CharacterSelectElem *>(char_select_elem_scene->instantiate());
        TextureRect *icon = static_cast<TextureRect *>(element->get_node_or_null(NodePath("Icon")));
        Ref<Texture> character_icon = ResourceLoader::load("res://scenes/ui/icons/characters/" + character_name + ".png");
        icon->set_texture(character_icon);

        Label *name = static_cast<Label *>(element->get_node_or_null(NodePath("Name")));
        name->set_text(character_name);
        elements->add_child(element);
    }
}

