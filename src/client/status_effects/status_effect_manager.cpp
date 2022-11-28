#include "status_effect_manager.hpp"
#include <core/io/dir_access.h>
#include <core/io/json.h>

#include "mercenaries/tundra/tundra_spiky_ball.hpp"

StatusEffectManager::StatusEffectManager()
{
    //Path where all deafult status effects are stored
    String defaultStatusEffectPath = "resources/status_effects";

    //

    loadDataFromDirectory();
}

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

Error StatusEffectManager::registerStatusEffect(StatusEffect *statusEffect)
{
    const String name = statusEffect->name;

    if(registeredStatusEffects.find(name) == registeredStatusEffects.end())
    {
        registeredStatusEffects.insert(name, statusEffect);

        return OK;
    }
    else
    {
        return ERR_DUPLICATE_SYMBOL;
    }
}
/*
//Previous Implementation
StatusEffect *StatusEffectManager::getRegisteredStatusEffect(String statusEffectName)
{
    auto it = registeredStatusEffects.find(statusEffectName);
    if(it != registeredStatusEffects.end())
    {
        StatusEffect *statusEffectData = it->value;

        return statusEffectData;
    }
    else
    {
        return nullptr;
    }
}
*/
bool StatusEffectManager::removeStatusEffect(String statusEffectName, Entity *target)
{
    if(StatusEffect* statusEffect = target->getStatusEffect(statusEffectName))
    {
        statusEffect->onExpire();
        //Remove status effect here?
        return true;
    }
    else
    {
        //Effect was not removed
        return false;
    }
}

StatusEffect* StatusEffectManager::getRegisteredStatusEffect(String statusEffectName)
{
    return registeredStatusEffects.get(statusEffectName);
}

StatusEffect *StatusEffectManager::applyStatusEffect(String statusEffectName, float durration, Entity *target, Entity *inflictor)
{
    /*
    What should happen if status effect limit is reached?
    - Status effects shouldn't have limit in the first place
    - Vector seems most suitable for that purpose
        - Entity should be able to store concurent status effect. If there are more - Vector takes care of reallocating it
    */

    //NOTE: Status effect should start ticking once entity enters the tree(is ready)
    if(StatusEffect *statusEffectInternal = getRegisteredStatusEffect(statusEffectName))
    {
        if(StatusEffect* statusEffectAppliedInstance = target->getStatusEffect(statusEffectName))
        {
            /*
            - If no buff with passed name is applied on entity, apply an instance of it.
            - If buff instance with passed name is applied on entity:
                - If buff is non-stackable: replace it with new instance
                - If buff is stackable: Add another stack to that buff instance 
                    - and reset duration(maybe inside StatusEffect?)
            */

   
            statusEffectAppliedInstance->addStacks(1);
        }
        else
        {
            StatusEffect* statusEffectInstance = statusEffectInternal->copy();

            target->appliedStatusEffects.append(statusEffectInstance);
            //Effect is considered active when onApply() is called
            statusEffectInstance->onApply();
        }
    }
    else
    {
        return nullptr;
    }
}

void StatusEffectManager::loadDataFromDirectory()
{
    //Load status effect data from *.json files.
    //File name will be the name status effect will be registered under
    //Allows loading after initialization

     //Register status effect based on data from each file
     
    /*
    Effect won't register if:
        - Effect with such name already exists
        - File failed to load
        - No read permission
        - JSON file is malformed
            - Invalid JSON syntax
            - Values inside JSON were of invalid type
    */

    Ref<DirAccess> dir = DirAccess::open("resources/status_effects");

    printf("%d\n", dir->get_files().size());

    for(auto fileName : dir->get_files())
    {
        printf("------------------------------------------\n");
        if(fileName.ends_with(".json"))
        {
            printf("%s\n", fileName.ascii().ptr());
            Error readErr;

            Ref<FileAccess> file = FileAccess::open(dir->get_current_dir()+"/"+fileName, FileAccess::READ, &readErr);

            if(readErr != OK)
            {
                printf("Error = %d\n", readErr);
            }
            else
            {
                String jsonStr = file->get_as_text(true);

                Ref<JSON> json = memnew(JSON);
                Error err = json->parse(jsonStr);

                if(err != OK)
                {
                   //Parse error at line x
                }
                else
                {
                    String effectName = fileName.substr(0, fileName.size() - 6);

                    /**
                     * Check what logic should be tied to that status effect
                    */
                    String logicObjectName = effectName;

                    if(StatusEffect* statusEffectReg = getRegisteredStatusEffect(effectName))
                    {
                        Dictionary data = Dictionary(json->get_data());
                        
                        statusEffectReg->loadData(data);
                    }
                    else
                    {
                        //No such status effect - ignoring
                    }
                }
            }
        }
    }

    for(auto effectData : registeredStatusEffects)
    {
        /*
        printf("Registered effect name = %s\n", effectData.value->name.ascii().ptr());
        printf("%s\n", String(*(effectData.value->statusEffectData)).ascii().ptr());  
        */      
    }

}