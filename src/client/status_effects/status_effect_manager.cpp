#include "status_effect_manager.hpp"

StatusEffectManager *StatusEffectManager::get_singleton()
{
    static StatusEffectManager instancePtr;
    return &instancePtr;
}

bool StatusEffectManager::isStatusEffectRegistered(std::string statusEffectName)
{
    if(registeredStatusEffects.find(statusEffectName) != registeredStatusEffects.end())
        return true;
    else
        return false;
}


StatusEffectManager::Error StatusEffectManager::registerStatusEffect(StatusEffectData *statusEffectData)
{
    const std::string name = statusEffectData->getName();

    if(registeredStatusEffects.find(name) == registeredStatusEffects.end())
    {
        registeredStatusEffects.insert(std::pair<std::string, StatusEffectData*>(name, statusEffectData));

        return OK;
    }
    else
    {
        return ALREADY_REGISTERED;
    }
}

StatusEffectData *StatusEffectManager::getStatusEffectData(std::string statusEffectName)
{
    auto it = registeredStatusEffects.find(statusEffectName);
    if(it != registeredStatusEffects.end())
    {
        StatusEffectData *statusEffectData = it->second;

        return statusEffectData;
    }
    else
    {
        return nullptr;
    }
}