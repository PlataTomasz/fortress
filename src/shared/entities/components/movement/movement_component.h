#if !defined(MOVEMENT_COMPONENT_INCLUDED)
#define MOVEMENT_COMPONENT_INCLUDED

#include "../component_3d.h"
#include <shared/data_holders/damage_object.hpp>

class Node3D;
class NavigationAgent3D;
class EntityStatsComponent;
class Entity;
class Ability;

/**
 * Node, which instantes control movement of an Entity
*/
class MovementComponent : public Component3D
{
GDCLASS(MovementComponent, Component3D);
#ifdef SERVER

#endif
private:
    bool currently_moving = false;

    NavigationAgent3D *nav_agent = nullptr;

    Vector3 previous_position;
    
    class CounteredLock {
    private:
        List<void *> locks;
    public:
        bool is_locked() {
            return locks.size() > 0;
        }
        
        void lock(void *key) {
            locks.push_back(key);
        }

        void unlock(void *key) {
            List<void *>::Element *e = locks.find(key);
            ERR_FAIL_NULL_MSG(e, "Passed object isn't locking this locker!");
            e->erase();
        }
    } movement_pause_locker;

    void _ready();
    void _on_entity_death(const Ref<DamageObject>& damage_object);
    void _tick();
    void _init();
    void _parented();
    void _frame();
    void _on_entity_revive();
    void _on_ability_use_start(Ability *ability);
    void _on_ability_use_finish(Ability *ability);
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    void clear_destination();
    void set_movement_processing(bool should_process_movement);

    void stop_movement();

    Entity *get_owning_entity();

    void set_navigation_agent(NavigationAgent3D *new_nav_agent);
    NavigationAgent3D *get_navigation_agent();

    void set_currently_moving(bool new_currently_moving);
    bool is_currently_moving();

    void set_pathfinding_radius(real_t pathfinding_radius);
    real_t get_pathfinding_radius();

    Vector3 get_destination_position();
    void set_destination_position(Vector3 target_pos);

    void pause_movement(void *who_paused);
    void unpause_movement(void *who_paused);
    bool is_movement_paused();
};

#endif // MOVEMENT_COMPONENT_INCLUDED