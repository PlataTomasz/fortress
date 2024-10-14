#include <shared/entities/structures/turret.h>
#include <scene/main/timer.h>

void Turret::server_rpc_recharge_started() {
    ERR_FAIL_MSG("Not implemented!");
}

void Turret::server_rpc_recharge_finished() {
    ERR_FAIL_MSG("Not implemented!");
}

void Turret::_on_attack_window_expire() {
    recharging = true;
    recharge_timer->start();
    rpc("server_rpc_recharge_started");
    emit_signal("recharge_started");
}

void Turret::_on_recharge_finished() {
    recharging = false;
    attack_window_timer->start();
    rpc("server_rpc_recharge_finished");
    emit_signal("recharge_finished");
}
