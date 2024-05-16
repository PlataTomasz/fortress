#include "player_hud.h"

#include <scene/gui/progress_bar.h>
#include <core/object/class_db.h>
#include <client/client.hpp>

#include <shared/entities/traits/t_has_attributes.h>

void PlayerHUD::_ready() {
    // Setup signals
    Client *client = static_cast<Client *>(get_node(NodePath("/root/Client")));
    ERR_FAIL_NULL(client);

    Ref<Player> ply = client->get_player();
    ERR_FAIL_NULL(ply);

    ply->connect("on_controlled_entity_changed", callable_mp(this, &PlayerHUD::_on_controlled_entity_changed));

    Entity *controlled_entity = ply->get_controlled_entity();
    ERR_FAIL_NULL(controlled_entity);

    // Initial
    _on_controlled_entity_changed(nullptr, controlled_entity);
}

void PlayerHUD::_on_controlled_entity_changed(Entity *old_entity, Entity *new_entity) {
    THasAttributes *t_has_attributes = dynamic_cast<THasAttributes *>(new_entity);
    ERR_FAIL_NULL(t_has_attributes);

    EntityAttributesComponent *attributes = t_has_attributes->get_attributes_component();
    ERR_FAIL_NULL(attributes);

    // Setup signals
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