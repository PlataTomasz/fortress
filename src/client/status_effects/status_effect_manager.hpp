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
     * Stores all registered status effects by their name
    */
    HashMap<String, StatusEffectData*> registeredStatusEffects;
public:
    static StatusEffectManager *get_singleton();

    bool isStatusEffectRegistered(String statusEffectName);
    /**
     * Registers status effect. If allowOverride is true, status effect will be overriden
    */
    Error registerStatusEffect(StatusEffectData *statusEffectData);

    StatusEffect *applyStatusEffect(String statusEffectName, float durration, Entity *target, Entity *inflictor);

    bool hasStatusEffect(String statusEffectName, Entity *ent);

    StatusEffectData *getStatusEffectData(String statusEffectName);

    //FIXME: Temporary fix to resolve linker error caused by template parameter
    /**
     * Loads status effects from files under path directory
    */
    void loadFromDirectory();
};

#endif // STATUS_EFFECT_MANAGER_HPP
