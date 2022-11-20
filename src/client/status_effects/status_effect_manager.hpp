#if !defined(STATUS_EFFECT_MANAGER_HPP)
#define STATUS_EFFECT_MANAGER_HPP

#include "status_effect.hpp"
#include <unordered_map>
#include <core/string/ustring.h>
#include "../entities/entity.hpp"

class StatusEffectManager
{
private:
    StatusEffectManager();

private:
    /**
     * Stores all registered status effects by their name
    */
    std::unordered_map<String, StatusEffectData*> registeredStatusEffects;
public:
    static StatusEffectManager *get_singleton();

    enum Error
    {
        OK = 0,
        ALREADY_REGISTERED,
        NO_SUCH_EFFECT,
    };

    bool isStatusEffectRegistered(String statusEffectName);
    /**
     * Registers status effect. If allowOverride is true, status effect will be overriden
    */
    StatusEffectManager::Error registerStatusEffect(StatusEffectData *statusEffectData);

    

    StatusEffectData *getStatusEffectData(String statusEffectName);
};

#endif // STATUS_EFFECT_MANAGER_HPP
