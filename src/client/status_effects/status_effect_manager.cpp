#include "status_effect_manager.hpp"
#include <core/io/dir_access.h>
#include <core/io/json.h>


StatusEffectManager::StatusEffectManager()
{
    //Path where all deafult status effects are stored
    std::string defaultStatusEffectPath = "resources/status_effects";

    //loadFromDirectory(defaultStatusEffectPath);
    loadFromDirectory();
}

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


Error StatusEffectManager::registerStatusEffect(StatusEffectData *statusEffectData)
{
    const std::string name = statusEffectData->getName();

    if(registeredStatusEffects.find(name) == registeredStatusEffects.end())
    {
        registeredStatusEffects.insert(std::pair<std::string, StatusEffectData*>(name, statusEffectData));

        return OK;
    }
    else
    {
        return ERR_DUPLICATE_SYMBOL;
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

                Ref<JSON> json;

                //printf("JSON parse error = %d\n", err);

                Variant data = json->parse_string(jsonStr);

                Variant k = Dictionary(data).get(Variant("name"), Variant());

                printf("Variant type: %d\n", k.get_type());

                printf("%s\n", jsonStr.ascii().ptr());
            }
        }
    }
}