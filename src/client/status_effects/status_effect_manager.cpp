#include "status_effect_manager.hpp"

StatusEffectManager *StatusEffectManager::get_singleton()
{
    static StatusEffectManager instancePtr;
    return &instancePtr;
}

bool StatusEffectManager::isStatusEffectRegistered(String statusEffectName)
{
    if(registeredStatusEffects.find(statusEffectName) != registeredStatusEffects.end())
        return true;
    else
        return false;
}

StatusEffectManager::Error StatusEffectManager::registerStatusEffect(StatusEffectData *statusEffectData)
{
    const String name = statusEffectData->getName();

    if(registeredStatusEffects.find(name) == registeredStatusEffects.end())
    {
        registeredStatusEffects.insert(std::pair<String, StatusEffectData*>(name, statusEffectData));

        return OK;
    }
    else
    {
        return ALREADY_REGISTERED;
    }
}

StatusEffectData *StatusEffectManager::getStatusEffectData(String statusEffectName)
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