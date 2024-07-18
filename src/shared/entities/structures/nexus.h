#if !defined(NEXUS_INCLUDED)
#define NEXUS_INCLUDED

#include <shared/entities/entity.h>

class Minion;
class Timer;

class Nexus : public Entity {
GDCLASS(Nexus, Entity);
private:
    Timer *minion_spawner_timer = nullptr;
    Timer *minion_spawn_interval_timer = nullptr;

    // TODO: Should be instantiated
    Minion *default_minion = nullptr;
    Minion *special_minion = nullptr;

    float spawner_timeout = 15.0;
    float interval_between_spawns = 1.0;

    int current_wave = 0;
    int WAVES_BEFORE_SPECIAL_WAVE = 3;

    int wave_spawned_minions = 0;
    int special_minions_per_wave = 1;
    int default_minions_per_wave = 4;

    Vector3 minion_spawning_position;

    void _spawn_minion(Vector3 where);
    void _spawn_special_minion(Vector3 where);

    void _spawn_minion_wave();
    void _spawn_minion_recursively();

    bool is_special_wave();
    int get_remaining_minion_spawn_amount();

    void _stop_spawning_minions();
    void _start_spawning_minions();
    void _pause_spawning_minions();

    void _initialize_timers();
protected:
    void _initv() override;
    void _readyv() override;
public:

};

#endif // NEXUS_INCLUDED
