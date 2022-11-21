#if !defined(STATUS_EFFECT_MANAGER_HPP)
#define STATUS_EFFECT_MANAGER_HPP

#include "status_effect.hpp"
#include <unordered_map>
//No hashing function for that type!
//#include <core/string/ustring.h>
#include <string>
#include "../entities/entity.hpp"
#include <core/templates/hash_map.h>

#include <filesystem>

namespace fs = std::filesystem;

class StatusEffectManager
{
private:
    StatusEffectManager();

private:
    /**
     * Stores all registered status effects by their name
    */
    std::unordered_map<std::string, StatusEffectData*> registeredStatusEffects;
public:
    static StatusEffectManager *get_singleton();

    bool isStatusEffectRegistered(std::string statusEffectName);
    /**
     * Registers status effect. If allowOverride is true, status effect will be overriden
    */
    Error registerStatusEffect(StatusEffectData *statusEffectData);

    StatusEffect *applyStatusEffect(std::string statusEffectName, float durration, Entity *target, Entity *inflictor);

    bool hasStatusEffect(std::string statusEffectName, Entity *ent);

    StatusEffectData *getStatusEffectData(std::string statusEffectName);

    //FIXME: Temporary fix to resolve linker error caused by template parameter
    /**
     * Loads status effects from files under path directory
    */
    void loadFromDirectory();
};

#endif // STATUS_EFFECT_MANAGER_HPP
