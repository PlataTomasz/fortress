#include "player_hud.h"

#include <scene/gui/progress_bar.h>
#include <core/object/class_db.h>
#include <client/client.hpp>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>

#include <shared/entities/mercenaries/mercenary.hpp>

#include <client/ui/ui.h>
#include <client/ui/status_effect_indicator.h>
#include <scene/gui/texture_rect.h>
#include <shared/core/sh_game.h>
#include <shared/gamemodes/gamemode.h>
#include <client/ui/game/abilities/ability_button.h>

#include <shared/entities/components/entity_stats/entity_attributes_component.h>

#include <shared/abilities/basic_attack.h>

void PlayerHUD::_ready() {
    // Setup signals
    Client *client = Client::get_instance();
    ERR_FAIL_NULL(client);

    SH_Game *game = client->get_shared_game();
    ERR_FAIL_NULL(game);

    Gamemode *gamemode = game->get_gamemode();
    if(gamemode) {
        _reconnect_gamemode_signals(gamemode);
    } else {
        // Not loaded yet - defer
        game->connect("post_level_load", callable_mp(this, &PlayerHUD::_on_level_ready));
    }

    Ref<Player> ply = client->get_player();
    ERR_FAIL_NULL(ply);

    ply->connect("on_controlled_entity_changed", callable_mp(this, &PlayerHUD::_on_controlled_mercenary_changed));

    Mercenary *controlled_entity = ply->get_controlled_entity();
    ERR_FAIL_NULL(controlled_entity);

    // Initial
    _on_controlled_mercenary_changed(controlled_entity);
}

void PlayerHUD::_on_level_ready() {
    Client *client = Client::get_instance();
    ERR_FAIL_NULL(client);

    SH_Game *game = client->get_shared_game();
    ERR_FAIL_NULL(game);

    Gamemode *gamemode = game->get_gamemode();
    ERR_FAIL_NULL(gamemode);

    _reconnect_gamemode_signals(gamemode);
}

void PlayerHUD::_reconnect_gamemode_signals(Gamemode *new_gamemode) {
    new_gamemode->connect("defeat", callable_mp(this, &PlayerHUD::_on_player_defeat));
    new_gamemode->connect("victory", callable_mp(this, &PlayerHUD::_on_player_victory));
}

// Player's controlled entity changed - Make UI read from new controlled entity
void PlayerHUD::_on_controlled_mercenary_changed(Mercenary *new_mercenary) {
    // Need to update values 
    EntityAttributesComponent *attributes = new_mercenary->get_attributes_component();
    ERR_FAIL_NULL(attributes);

    StatusEffectVictimComponent *status_effect_component = new_mercenary->get_status_effect_victim_component();
    if (status_effect_component) {
        status_effect_component->connect("status_effect_gained", callable_mp(this, &PlayerHUD::_on_self_status_effect_gain));
        status_effect_component->connect("status_effect_lost", callable_mp(this, &PlayerHUD::_on_self_status_effect_removed));

        //Add current StatusEffects to be rendered on UI
        List<StatusEffect *> status_effects = status_effect_component->get_status_effects();
        for (StatusEffect *status_effect : status_effects) {
            StatusEffectIndicator *status_effect_indicator = UI::create_status_effect_indicator(status_effect);
            if(status_effect_indicator != nullptr) {
                status_effect_area->add_child(status_effect_indicator);
            }
        }
    }

    // Setup signals
    _on_current_health_changed(attributes->get_health()->get_current());
    attributes->get_health()->connect("current_value_changed", callable_mp(this, &PlayerHUD::_on_current_health_changed));
    print_line("PlayerHUD::_on_controlled_mercenary_changed::ent:", new_mercenary->to_string());
    print_line("PlayerHUD::_on_controlled_mercenary_changed::health_attribute:",attributes->get_health()->to_string());

    // Change displayed character portrait
    character_portrait->set_texture(new_mercenary->get_portrait_icon());

    // TODO: Disconnect signals from old entity if old_entity is valid

    if(AbilityCasterComponent *ability_caster_component = new_mercenary->get_ability_caster_component()) {
        _reinitialize_ability_buttons(ability_caster_component);
    }
}

void PlayerHUD::_reinitialize_ability_buttons(AbilityCasterComponent *ability_caster_component) {
    basic_attack_button->set_ability(ability_caster_component->get_basic_attack());
    passive_ability_button->set_ability(ability_caster_component->get_passive_ability());
    first_ability_button->set_ability(ability_caster_component->get_first_ability());
    second_ability_button->set_ability(ability_caster_component->get_second_ability());
    third_ability_button->set_ability(ability_caster_component->get_third_ability());
    ultimate_ability_button->set_ability(ability_caster_component->get_ultimate_ability());
}

void PlayerHUD::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			break;

		default:
			break;
	}
}

void PlayerHUD::_on_current_health_changed(float new_health) {
    ERR_FAIL_NULL(health_bar);
    health_bar->set_value(new_health);
}

void PlayerHUD::_on_self_status_effect_gain(StatusEffect *status_effect) {
    // Currently the same indicator is used for all status effects
    StatusEffectIndicator *status_effect_indicator = UI::create_status_effect_indicator(status_effect);
    ERR_FAIL_NULL_MSG(status_effect_indicator, "Creating UI representation for status effect failed!");
    status_effect_area->add_child(status_effect_indicator);
}

void PlayerHUD::_on_self_status_effect_removed(StatusEffect *status_effect) {
    // Naive implementation - iterate over all exisiting status effect indicators and remove matching one
    TypedArray<Node> status_effect_indicator_children = status_effect_area->get_children();
    for(int i = 0;i < status_effect_indicator_children.size();i++) {
        StatusEffectIndicator *indicator = static_cast<StatusEffectIndicator *>(
            status_effect_indicator_children[i].operator Object*()
        );

        if (indicator->get_status_effect() == status_effect) {
            // Found it, break the loop
            indicator->queue_free();
            return;
        }
    }
}

void PlayerHUD::_on_self_health_changed(float p_health) {
    health_bar->set_value(p_health);
}

void PlayerHUD::set_health_bar(ProgressBar *p_health_bar) {
    health_bar = p_health_bar;
}

ProgressBar *PlayerHUD::get_health_bar() {
    return health_bar;
}

void PlayerHUD::set_status_effect_area(Control *p_status_effect_area) {
    status_effect_area = p_status_effect_area;
}

Control *PlayerHUD::get_status_effect_area() {
    return status_effect_area;
}

void PlayerHUD::set_character_portrait(TextureRect *p_character_portrait) {
    character_portrait = p_character_portrait;
}

TextureRect *PlayerHUD::get_character_portrait() {
    return character_portrait;
}

void PlayerHUD::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_health_bar"), &PlayerHUD::get_health_bar);
    ::ClassDB::bind_method(D_METHOD("set_health_bar"), &PlayerHUD::set_health_bar);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "health_bar", PROPERTY_HINT_NODE_TYPE, ProgressBar::get_class_static()), "set_health_bar", "get_health_bar");

    ::ClassDB::bind_method(D_METHOD("get_status_effect_area"), &PlayerHUD::get_status_effect_area);
    ::ClassDB::bind_method(D_METHOD("set_status_effect_area"), &PlayerHUD::set_status_effect_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "status_effect_area", PROPERTY_HINT_NODE_TYPE, Control::get_class_static()), "set_status_effect_area", "get_status_effect_area");

    ::ClassDB::bind_method(D_METHOD("get_character_portrait"), &PlayerHUD::get_character_portrait);
    ::ClassDB::bind_method(D_METHOD("set_character_portrait"), &PlayerHUD::set_character_portrait);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "character_portrait", PROPERTY_HINT_NODE_TYPE, TextureRect::get_class_static()), "set_character_portrait", "get_character_portrait");

    ::ClassDB::bind_method(D_METHOD("get_victory_screen"), &PlayerHUD::get_victory_screen);
    ::ClassDB::bind_method(D_METHOD("set_victory_screen"), &PlayerHUD::set_victory_screen);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "victory_screen", PROPERTY_HINT_NODE_TYPE, Control::get_class_static()), "set_victory_screen", "get_victory_screen");

    ::ClassDB::bind_method(D_METHOD("get_defeat_screen"), &PlayerHUD::get_defeat_screen);
    ::ClassDB::bind_method(D_METHOD("set_defeat_screen"), &PlayerHUD::set_defeat_screen);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "defeat_screen", PROPERTY_HINT_NODE_TYPE, Control::get_class_static()), "set_defeat_screen", "get_defeat_screen");

    ::ClassDB::bind_method(D_METHOD("get_basic_attack_button"), &PlayerHUD::get_basic_attack_button);
    ::ClassDB::bind_method(D_METHOD("set_basic_attack_button"), &PlayerHUD::set_basic_attack_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "basic_attack_button", PROPERTY_HINT_NODE_TYPE, ActiveAbilityButton::get_class_static()), "set_basic_attack_button", "get_basic_attack_button");

    ::ClassDB::bind_method(D_METHOD("get_passive_ability_button"), &PlayerHUD::get_passive_ability_button);
    ::ClassDB::bind_method(D_METHOD("set_passive_ability_button"), &PlayerHUD::set_passive_ability_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "passive_ability_button", PROPERTY_HINT_NODE_TYPE, ActiveAbilityButton::get_class_static()), "set_passive_ability_button", "get_passive_ability_button");

    ::ClassDB::bind_method(D_METHOD("get_first_ability_button"), &PlayerHUD::get_first_ability_button);
    ::ClassDB::bind_method(D_METHOD("set_first_ability_button"), &PlayerHUD::set_first_ability_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "first_ability_button", PROPERTY_HINT_NODE_TYPE, ActiveAbilityButton::get_class_static()), "set_first_ability_button", "get_first_ability_button");

    ::ClassDB::bind_method(D_METHOD("get_second_ability_button"), &PlayerHUD::get_second_ability_button);
    ::ClassDB::bind_method(D_METHOD("set_second_ability_button"), &PlayerHUD::set_second_ability_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "second_ability_button", PROPERTY_HINT_NODE_TYPE, ActiveAbilityButton::get_class_static()), "set_second_ability_button", "get_second_ability_button");

    ::ClassDB::bind_method(D_METHOD("get_third_ability_button"), &PlayerHUD::get_third_ability_button);
    ::ClassDB::bind_method(D_METHOD("set_third_ability_button"), &PlayerHUD::set_third_ability_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "third_ability_button", PROPERTY_HINT_NODE_TYPE, ActiveAbilityButton::get_class_static()), "set_third_ability_button", "get_third_ability_button");

    ::ClassDB::bind_method(D_METHOD("get_ultimate_ability_button"), &PlayerHUD::get_ultimate_ability_button);
    ::ClassDB::bind_method(D_METHOD("set_ultimate_ability_button"), &PlayerHUD::set_ultimate_ability_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ultimate_ability_button", PROPERTY_HINT_NODE_TYPE, ActiveAbilityButton::get_class_static()), "set_ultimate_ability_button", "get_ultimate_ability_button");
}

Control *PlayerHUD::get_victory_screen() {
    return victory_screen;
}

void PlayerHUD::set_victory_screen(Control *new_victory_screen) {
    victory_screen = new_victory_screen;
}

Control *PlayerHUD::get_defeat_screen() {
    return defeat_screen;
}

void PlayerHUD::set_defeat_screen(Control *new_defeat_screen) {
    defeat_screen = new_defeat_screen;
}

void PlayerHUD::show_victory_screen() {
    ERR_FAIL_NULL(victory_screen);
    victory_screen->set_visible(true);
}

void PlayerHUD::show_defeat_screen() {
    ERR_FAIL_NULL(defeat_screen);
    defeat_screen->set_visible(true);
}

void PlayerHUD::_on_player_defeat() {
    show_defeat_screen();
}

void PlayerHUD::_on_player_victory() {
    show_victory_screen();
}

ActiveAbilityButton *PlayerHUD::get_basic_attack_button() {
    return basic_attack_button;
}

void PlayerHUD::set_basic_attack_button(ActiveAbilityButton *new_ability_button) {
    basic_attack_button = new_ability_button;
}

ActiveAbilityButton *PlayerHUD::get_passive_ability_button() {
    return passive_ability_button;
}

void PlayerHUD::set_passive_ability_button(ActiveAbilityButton *new_ability_button) {
    passive_ability_button = new_ability_button;
}

ActiveAbilityButton *PlayerHUD::get_first_ability_button() {
    return first_ability_button;
}

void PlayerHUD::set_first_ability_button(ActiveAbilityButton *new_ability_button) {
    first_ability_button = new_ability_button;
}

ActiveAbilityButton *PlayerHUD::get_second_ability_button() {
    return second_ability_button;
}

void PlayerHUD::set_second_ability_button(ActiveAbilityButton *new_ability_button) {
    second_ability_button = new_ability_button;
}

ActiveAbilityButton *PlayerHUD::get_third_ability_button() {
    return third_ability_button;
}

void PlayerHUD::set_third_ability_button(ActiveAbilityButton *new_ability_button) {
   third_ability_button = new_ability_button;
}

ActiveAbilityButton *PlayerHUD::get_ultimate_ability_button() {
    return ultimate_ability_button;
}

void PlayerHUD::set_ultimate_ability_button(ActiveAbilityButton *new_ability_button) {
    ultimate_ability_button = new_ability_button;
}