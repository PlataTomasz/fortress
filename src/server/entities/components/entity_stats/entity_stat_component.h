#if !defined(ENTITY_STATS_INCLUDED)
#define ENTITY_STATS_INCLUDED

#include "../component.h"
#include "capped_stat.h"

class EntityStatsComponent : public Component
{
private:
    
protected:

public:
    Ref<CappedStat> health;
    //Reduces damage no matter damage type
    Ref<Stat> global_defense;

    Ref<Stat> attack_damage;
    Ref<Stat> attack_speed;
    Ref<Stat> magic_power;
    Ref<Stat> damage_rampup;
    Ref<Stat> cooldown_reduction;
    Ref<Stat> movement_speed;

    //NOTE: Only necessary setters and getters are exposed to Godot atm
    void set_movement_speed(Ref<Stat> p_movement_speed)
    {
        movement_speed = p_movement_speed;
    }
    
    Ref<Stat> get_movement_speed()
    {
        return movement_speed;
    }
};

#endif // ENTITY_STATS_INCLUDED