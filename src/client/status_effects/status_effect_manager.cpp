#include "status_effect_manager.hpp"
#include <core/io/dir_access.h>
#include <core/io/json.h>



StatusEffectManager::StatusEffectManager()
{
    //Path where all deafult status effects are stored
    String defaultStatusEffectPath = "resources/status_effects";

    //loadFromDirectory(defaultStatusEffectPath);
    loadFromDirectory();
    loadStatusEffectBehaviours();
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


Error StatusEffectManager::registerStatusEffect(StatusEffectData *statusEffectData)
{
    const String name = statusEffectData->getName();

    if(registeredStatusEffects.find(name) == registeredStatusEffects.end())
    {
        registeredStatusEffects.insert(name, statusEffectData);

        return OK;
    }
    else
    {
        return ERR_DUPLICATE_SYMBOL;
    }
}

StatusEffectData *StatusEffectManager::getStatusEffectData(String statusEffectName)
{
    auto it = registeredStatusEffects.find(statusEffectName);
    if(it != registeredStatusEffects.end())
    {
        StatusEffectData *statusEffectData = it->value;

        return statusEffectData;
    }
    else
    {
        return nullptr;
    }
}

void StatusEffectManager::loadFromDirectory()
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
                    Dictionary jsonData = Dictionary(json->get_data());

                    //Loading from JSON works

                    String effectName = fileName.substr(0, fileName.size() - 6);

                    //What icon does the buff have?
                    String iconName;


                    printf("EffectName = %s\n", effectName.ascii().ptr());

                    //If type is invalid 0 is set instead
                    int maxStacks = int(jsonData.get("maxStacks", 5));
                    int damage = int(jsonData.get("damage", 5));
                    int duration = int(jsonData.get("duration", 5));

                    /**
                     * Check what logic should be tied to that status effect
                    */
                    String logicObjectName = effectName;

                    StatusEffectBehaviour *statusEffectBehaviour;

                    printf("Damage = %d\n", damage);
                    printf("Duration = %d\n", duration);


                    StatusEffectData *statusEffectData = new StatusEffectData(
                        effectName,
                        maxStacks,
                        damage,
                        duration
                        //statusEffectBehaviour
                    );



                    registerStatusEffect(statusEffectData);

                    printf("Size registered effects: %d\n", registeredStatusEffects.size());

                    for(auto effectData : registeredStatusEffects)
                    {
                        printf("Saved effect name = %s\n", effectData.value->getName().ascii().ptr());
                    }
                }
            }
        }
    }
}