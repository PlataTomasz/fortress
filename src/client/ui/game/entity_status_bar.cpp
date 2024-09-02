#include "entity_status_bar.h"

#include <shared/entities/entity.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <client/ui/ui.h>
#include <client/ui/status_effect_indicator.h>
#include <shared/status_effects/status_effect.hpp>

void EntityStatusBar::_update_status_bar() {
    DISABLE_IN_EDITOR();
    ERR_FAIL_NULL(ent);
    StatusEffectVictimComponent *status_effect_component = ent->get_component<StatusEffectVictimComponent>();
    ERR_FAIL_NULL(status_effect_component);

    status_effect_component->connect("status_effect_gained", callable_mp(this, &EntityStatusBar::_on_status_effect_gain));
    status_effect_component->connect("status_effect_lost", callable_mp(this, &EntityStatusBar::_on_status_effect_removed));
    
    List<StatusEffect *> status_effect_list = status_effect_component->get_status_effects();

    for(StatusEffect *status_effect : status_effect_list) {
        // Create indicator for each status effect
        StatusEffectIndicator *status_effect_indicator = UI::create_status_effect_indicator(status_effect);
        status_effect_indicator->set_tooltip_enabled(false);
        add_child(status_effect_indicator);
    }
}

void EntityStatusBar::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_entity"), &EntityStatusBar::get_entity);
    ::ClassDB::bind_method(D_METHOD("set_entity"), &EntityStatusBar::set_entity);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_NODE_TYPE, Entity::get_class_static()), "set_entity", "get_entity");
}

void EntityStatusBar::_on_status_effect_gain(StatusEffect *status_effect) {
    ERR_FAIL_NULL(status_effect);
    // Currently the same indicator is used for all status effects
    StatusEffectIndicator *status_effect_indicator = UI::create_status_effect_indicator(status_effect);
    ERR_FAIL_NULL_MSG(status_effect_indicator, "Creating UI representation for status effect failed!");
    status_effect_indicator->set_tooltip_enabled(false);
    add_child(status_effect_indicator);
}

void EntityStatusBar::_on_status_effect_removed(StatusEffect *status_effect) {
    // Naive implementation - iterate over all exisiting status effect indicators and remove matching one
    TypedArray<Node> status_effect_indicator_children = get_children();
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