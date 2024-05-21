#include "player_hud.h"

#include <scene/gui/progress_bar.h>
#include <core/object/class_db.h>
#include <client/client.hpp>

#include <shared/entities/traits/t_has_attributes.h>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>

#include <shared/entities/mercenaries/mercenary.hpp>

void PlayerHUD::_ready() {
    // Setup signals
    Client *client = static_cast<Client *>(get_node(NodePath("/root/Client")));
    ERR_FAIL_NULL(client);

    Ref<Player> ply = client->get_player();
    ERR_FAIL_NULL(ply);

    ply->connect("on_controlled_entity_changed", callable_mp(this, &PlayerHUD::_on_controlled_mercenary_changed));

    Mercenary *controlled_entity = ply->get_controlled_entity();
    ERR_FAIL_NULL(controlled_entity);

    // Initial
    _on_controlled_mercenary_changed(nullptr, controlled_entity);
}

// Player's controlled entity changed - Make UI read from new controlled entity
void PlayerHUD::_on_controlled_mercenary_changed(Mercenary *old_mercenary, Mercenary *new_mercenary) {
    // Need to update values 
    EntityAttributesComponent *attributes = new_mercenary->get_attributes_component();
    ERR_FAIL_NULL(attributes);

    StatusEffectVictimComponent *status_effect_component = new_mercenary->get_status_effect_victim_component();
    ERR_FAIL_NULL(status_effect_component);

    // Setup signals
    _on_current_health_changed(health_bar->get_value(), attributes->get_health()->get_current());
    attributes->get_health()->connect("current_value_changed", callable_mp(this, &PlayerHUD::_on_current_health_changed));


    // TODO: Disconnect signals from old entity if old_entity is valid
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

void PlayerHUD::_on_current_health_changed(float old_health, float new_health) {
    ERR_FAIL_NULL(health_bar);
    health_bar->set_value(new_health);
}

void PlayerHUD::_on_self_status_effect_gain() {
    // Add status effect icon
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

void PlayerHUD::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_health_bar"), &PlayerHUD::get_health_bar);
    ::ClassDB::bind_method(D_METHOD("set_health_bar"), &PlayerHUD::set_health_bar);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "health_bar", PROPERTY_HINT_NODE_TYPE, "ProgressBar"), "set_health_bar", "get_health_bar");
}