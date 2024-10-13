#include "turret_recharge_indicator.h"

#include <shared/entities/structures/turret.h>

void TurretRechargeIndicator::_on_recharge_started() {
    set_visible(true);
}

void TurretRechargeIndicator::_on_recharge_finished() {
    set_visible(false);
}

void TurretRechargeIndicator::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_DRAW: {
			_draw();
		} break;

		case NOTIFICATION_READY: {
            _ready();
		} break;

		default:
			break;
	}
}

void TurretRechargeIndicator::_draw() {
    // Get maximum recharge time as maximum displayed on bar
    // Get current recharge time as current value displayed on bar
    float a = turret->get_current_recharge_time();
    float b = turret->get_max_recharge_time();

    if(progress_bar) {
        float progress_bar_percentage = (turret->get_current_recharge_time() / turret->get_max_recharge_time())*100;
        progress_bar->set_value(progress_bar_percentage);
    }
}

void TurretRechargeIndicator::_ready() {
    ERR_FAIL_NULL(turret);
    ERR_FAIL_NULL(progress_bar);

    turret->connect("recharge_started", callable_mp(this, &TurretRechargeIndicator::_on_recharge_started));
    turret->connect("recharge_finished", callable_mp(this, &TurretRechargeIndicator::_on_recharge_finished));
}

void TurretRechargeIndicator::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_turret"), &TurretRechargeIndicator::get_turret);
    ::ClassDB::bind_method(D_METHOD("set_turret"), &TurretRechargeIndicator::set_turret);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "turret", PROPERTY_HINT_NODE_TYPE, Turret::get_class_static()), "set_turret", "get_turret");
    ::ClassDB::bind_method(D_METHOD("get_progress_bar"), &TurretRechargeIndicator::get_progress_bar);
    ::ClassDB::bind_method(D_METHOD("set_progress_bar"), &TurretRechargeIndicator::set_progress_bar);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "progress_bar", PROPERTY_HINT_NODE_TYPE, Range::get_class_static()), "set_progress_bar", "get_progress_bar");
}

void TurretRechargeIndicator::set_turret(Turret *new_turret) {
    turret = new_turret;
}

Turret *TurretRechargeIndicator::get_turret() {
    return turret;
}

void TurretRechargeIndicator::set_progress_bar(Range *new_progress_bar) {
    progress_bar = new_progress_bar;
}

Range *TurretRechargeIndicator::get_progress_bar() {
    return progress_bar;
}