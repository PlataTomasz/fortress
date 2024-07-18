#include "nexus.h"

#include <scene/main/timer.h>

void Nexus::_initv() {
    _initialize_timers();
}

void Nexus::_initialize_timers() {
    minion_spawner_timer = memnew(Timer);
    minion_spawner_timer->set_wait_time(spawner_timeout);
    minion_spawner_timer->connect("timeout", callable_mp(this, &Nexus::_spawn_minion_wave));
    minion_spawner_timer->set_autostart(true);
    minion_spawner_timer->set_name("WaveSpawnInterval");
    add_child(minion_spawner_timer);

    minion_spawn_interval_timer = memnew(Timer);
    minion_spawn_interval_timer->set_wait_time(interval_between_spawns);
    minion_spawn_interval_timer->connect("timeout", callable_mp(this, &Nexus::_spawn_minion_recursively));
    minion_spawner_timer->set_autostart(true);
    minion_spawn_interval_timer->set_paused(true);
    minion_spawn_interval_timer->set_name("MinionSpawnInterval");
    add_child(minion_spawn_interval_timer);
}

void Nexus::_readyv() {
    _spawn_minion_wave();
}

void Nexus::_spawn_minion_wave() {
    wave_spawned_minions = 0;
    current_wave++;

    _start_spawning_minions();
}

bool Nexus::is_special_wave() {
    return current_wave >= WAVES_BEFORE_SPECIAL_WAVE;
}

int Nexus::get_remaining_minion_spawn_amount() {
    if(is_special_wave()) {
        int total_minions_per_wave = special_minions_per_wave + default_minions_per_wave;
        return total_minions_per_wave - wave_spawned_minions;
    } else {
        int total_minions_per_wave = default_minions_per_wave;
        return total_minions_per_wave - wave_spawned_minions;
    }
}

// TODO: Better name - It should spawn minions at intervals until there are no minions left to spawn
void Nexus::_spawn_minion_recursively() {
    if(is_special_wave() && get_remaining_minion_spawn_amount() <= special_minions_per_wave) {
        // All default minions spawned, spawn wave with special minion
        _spawn_special_minion(minion_spawning_position);
    } else {
        _spawn_minion(minion_spawning_position);
    }

    wave_spawned_minions++;

    if(get_remaining_minion_spawn_amount() <= 0) {
        _stop_spawning_minions();
    }
}

void Nexus::_stop_spawning_minions() {
    minion_spawn_interval_timer->stop();
}

void Nexus::_start_spawning_minions() {
    minion_spawn_interval_timer->start();
    minion_spawn_interval_timer->set_paused(false);
}

void Nexus::_pause_spawning_minions() {
    minion_spawn_interval_timer->set_paused(true);
}

void Nexus::_spawn_minion(Vector3 where) {
    print_line("PLACEHOLDER: Default minion spawned at: " + where);
}

void Nexus::_spawn_special_minion(Vector3 where) {
    print_line("PLACEHOLDER: Special minion spawned at: " + where);
}