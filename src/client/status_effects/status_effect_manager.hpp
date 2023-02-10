#if !defined(STATUS_EFFECT_MANAGER_HPP)
#define STATUS_EFFECT_MANAGER_HPP

#include "status_effect.hpp"
#include <variant/string.hpp>
#include "../entities/entity.hpp"
#include <templates/hash_map.hpp>

class StatusEffectManager
{
private:
    StatusEffectManager();

private:
    /**
     * Stores all registered status effects by their name. These are default objects and converted into instances via copy constructor.
    */
    HashMap<String, StatusEffect*> registeredStatusEffects;
public:
    static StatusEffectManager *get_singleton();

    bool isStatusEffectRegistered(String statusEffectName);
    /**
     * Registers status effect. If allowOverride is true, status effect will be overriden
    */
    Error registerStatusEffect(String name, StatusEffect *statusEffect);

    StatusEffect *applyStatusEffect(String statusEffectName, float durration, Entity *target, Entity *inflictor);

    /**
     * Removes status effect from target Entity
    */
    bool removeStatusEffect(String statusEffectName, Entity *target);

    bool hasStatusEffect(String statusEffectName, Entity *ent);

    StatusEffect *getRegisteredStatusEffect(String statusEffectName);


    /**
     * Loads status effects from files under path directory
    */
    void loadDataFromDirectory();
};

#endif // STATUS_EFFECT_MANAGER_HPP
