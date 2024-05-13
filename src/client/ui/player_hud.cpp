#include "player_hud.h"

#include <scene/gui/progress_bar.h>
#include <core/object/class_db.h>

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