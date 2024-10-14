#include <shared/entities/structures/turret.h>
#include <scene/main/timer.h>

void Turret::server_rpc_recharge_started() {
    recharge_timer->start();
    emit_signal("recharge_started");
}

void Turret::server_rpc_recharge_finished() {
    attack_window_timer->start();
    emit_signal("recharge_finished");
}

void Turret::_on_attack_window_expire() {

}

void Turret::_on_recharge_finished() {

}
