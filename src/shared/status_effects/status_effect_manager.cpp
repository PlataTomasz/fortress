#include "status_effect_manager.hpp"
#include <core/io/dir_access.h>
#include <core/io/json.h>
#include <core/io/file_access.h>

#include <shared/status_effects/status_effect_instance.h>

#include "./mercenaries/tundra/tundra_spiky_ball.hpp"

StatusEffectManager::StatusEffectManager()
{
    print_line("StatusEffectManager init...");
    initialize_from_resources();
    print_line("StatusEffectManager init finished!");
}

StatusEffectManager *StatusEffectManager::get_singleton()
{
    static StatusEffectManager instancePtr;

    return &instancePtr;
}

bool StatusEffectManager::is_status_effect_registered(StringName statusEffectName)
{
    if(registered_status_effects.find(statusEffectName) != registered_status_effects.end())
        return true;
    else
        return false;
}

Error StatusEffectManager::register_status_effect(StringName name, StatusEffect *statusEffect)
{
    if(registered_status_effects.find(name) == registered_status_effects.end())
    {
        registered_status_effects.insert(name, statusEffect);

        return OK;
    }
    else
    {
        return ERR_DUPLICATE_SYMBOL;
    }
}

//Removes registered status effect, making it impossible to create new instances of this StatusEffect via StatusEffectManager
void StatusEffectManager::unregister(StringName status_effect_name)
{
    //TODO: Implement
}

void StatusEffectManager::initialize_from_resources()
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

    String load_path = "res://resources/status_effects";
    Ref<DirAccess> dir_access = DirAccess::open(load_path);

    print_line("Loading status effects from resource path...");

    for(auto fileName : dir_access->get_files())
    {
        //Effect name is based on filename without it's extension
        String name = fileName.split(".")[0]; //Empty filename won't be a problem(i hope?)

        Ref<StatusEffect> status_effect = ResourceLoader::load(load_path);

        registered_status_effects.insert(name, status_effect);

        print_line(String(name) + "loaded!");

    }
}


StatusEffectInstance *StatusEffectManager::create_status_effect_instance(StringName effect_name)
{

}