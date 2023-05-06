#if !defined(STATUS_EFFECT_MANAGER_HPP)
#define STATUS_EFFECT_MANAGER_HPP

#include "status_effect.hpp"
#include <core/string/ustring.h>
#include "../entities/entity.hpp"
#include <core/templates/hash_map.h>

class StatusEffectManager
{
private:
    StatusEffectManager();

private:
    /**
     * Stores all registered status effects by their name. These are default objects and converted into instances via copy constructor.
    */
    HashMap<String, StatusEffect*> registered_status_effects;
public:
    static StatusEffectManager *get_singleton();

    bool is_status_effect_registered(String status_effect_name);
    /**
     * Registers status effect. If allowOverride is true, status effect will be overriden
    */
    Error register_status_effect(String name, StatusEffect* status_effect);

    StatusEffect *apply_status_effect(String status_effect_name, float durration, Entity *target, Entity *inflictor);

    /**
     * Removes status effect from target Entity
    */
    bool remove_status_effect(String status_effect_name, Entity* target);
    bool remove_status_effect(StatusEffect* status_effect, Entity* target);

    bool has_status_effect(String status_effect_name, Entity* ent);

    StatusEffect *get_registered_status_effect(String status_effect_name);


    /**
     * Loads status effects from files under path directory
    */
    void load_data_from_directory();
};

#endif // STATUS_EFFECT_MANAGER_HPP
