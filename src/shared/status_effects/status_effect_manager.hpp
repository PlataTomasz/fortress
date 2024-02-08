#if !defined(STATUS_EFFECT_MANAGER_HPP)
#define STATUS_EFFECT_MANAGER_HPP

#include "status_effect.hpp"
#include <core/string/ustring.h>
#include <shared/entities/entity.h>
#include <core/templates/hash_map.h>

class StatusEffectInstance;

//TODO: Move to StatusEffectInflictorComponent and StatusEffectVictimComponent
class StatusEffectManager
{
private:
    StatusEffectManager();
    
private:
    /**
     * Stores all registered status effects by their name. These are default objects and converted into instances via copy constructor.
    */
    HashMap<String, Ref<StatusEffect>> registered_status_effects;
public:
    static StatusEffectManager *get_singleton();

    bool is_status_effect_registered(StringName status_effect_name);
    /**
     * Registers new status effect
    */
    Error register_status_effect(StringName name, StatusEffect *status_effect);

    void unregister(StringName status_effect_name);

    //Creates new status effect instance from StatusEffect based on It's name
    StatusEffectInstance *create_status_effect_instance(StringName effect_name);

    /**
     * Loads status effects from resource files at "res://status_effects"
    */
    void initialize_from_resources();
};

#endif // STATUS_EFFECT_MANAGER_HPP
