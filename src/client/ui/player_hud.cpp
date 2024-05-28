#include "player_hud.h"

#include <scene/gui/progress_bar.h>
#include <core/object/class_db.h>
#include <client/client.hpp>

#include <shared/entities/traits/t_has_attributes.h>

#include <shared/entities/components/status_effects/status_effect_victim_component.h>

#include <shared/entities/mercenaries/mercenary.hpp>

#include <client/ui/ui.h>
#include <client/ui/status_effect_indicator.h>

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
    if(attributes) {

    }

    StatusEffectVictimComponent *status_effect_component = new_mercenary->get_status_effect_victim_component();
    if (status_effect_component) {
        status_effect_component->connect("child_entered_tree", callable_mp(this, &PlayerHUD::_on_self_status_effect_gain));
        status_effect_component->connect("child_exiting_tree", callable_mp(this, &PlayerHUD::_on_self_status_effect_removed));

        //Add current StatusEffects to be rendered on UI
        TypedArray<Node> status_effects = status_effect_component->get_children();
        for (int i = 0;i<status_effects.size();i++) {
            StatusEffect *status_effect = static_cast<StatusEffect *>(status_effects[i].operator Object *());

            StatusEffectIndicator *status_effect_indicator = UI::create_status_effect_indicator(status_effect);
            if(status_effect_indicator != nullptr) {
                status_effect_area->add_child(status_effect_indicator);
            }
        }
    }

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


void PlayerHUD::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_health_bar"), &PlayerHUD::get_health_bar);
    ::ClassDB::bind_method(D_METHOD("set_health_bar"), &PlayerHUD::set_health_bar);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "health_bar", PROPERTY_HINT_NODE_TYPE, "ProgressBar"), "set_health_bar", "get_health_bar");

    ::ClassDB::bind_method(D_METHOD("get_status_effect_area"), &PlayerHUD::get_status_effect_area);
    ::ClassDB::bind_method(D_METHOD("set_status_effect_area"), &PlayerHUD::set_status_effect_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "status_effect_area", PROPERTY_HINT_NODE_TYPE, "Control"), "set_status_effect_area", "get_status_effect_area");
}