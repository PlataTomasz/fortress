#include "status_effect_manager.hpp"
#include <core/io/dir_access.h>
#include <core/io/json.h>
#include <core/io/file_access.h>

#include "mercenaries/tundra/tundra_spiky_ball.hpp"

StatusEffectManager::StatusEffectManager()
{
    //Path where all deafult status effects are stored
    String defaultStatusEffectPath = "resources/status_effects";

    //Register empty status effects as templates for copying
    register_status_effect("tundra_spiky_ball", new TundraSpikyBallStatus());


    load_data_from_directory();
}

StatusEffectManager *StatusEffectManager::get_singleton()
{
    static StatusEffectManager instancePtr;

    return &instancePtr;
}

bool StatusEffectManager::is_status_effect_registered(String statusEffectName)
{
    if(registered_status_effects.find(statusEffectName) != registered_status_effects.end())
        return true;
    else
        return false;
}

Error StatusEffectManager::register_status_effect(String name, StatusEffect *statusEffect)
{
    //const String name = statusEffect->name;

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
bool StatusEffectManager::remove_status_effect(String statusEffectName, Entity *target)
{
    StatusEffect* statusEffect = target->get_status_effect(statusEffectName);
    if(statusEffect && !statusEffect->is_permament())
    {
        statusEffect->on_expire();
        auto hashMapIter = target->applied_status_effects.find(statusEffectName);
        target->applied_status_effects.remove(hashMapIter);

        return true;
    }
    else
    {
        //Effect was not removed
        return false;
    }
}

bool StatusEffectManager::remove_status_effect(StatusEffect* status_effect, Entity* target)
{
    if(status_effect && !status_effect->is_permament())
    {
        status_effect->on_expire();
        auto hashMapIter = target->applied_status_effects.find(status_effect->name);
        target->applied_status_effects.remove(hashMapIter);

        return true;
    }
    else
    {
        //Effect was not removed
        return false;
    }
}

StatusEffect* StatusEffectManager::get_registered_status_effect(String status_effect_name)
{
    if(registered_status_effects.has(status_effect_name))
    {
        return registered_status_effects.get(status_effect_name);
    }
    else
    {
        return nullptr;
    }
}

StatusEffect *StatusEffectManager::apply_status_effect(String status_effect_name, float duration, Entity *target, Entity *inflictor)
{
    /*
    What should happen if status effect limit is reached?
    - Status effects shouldn't have limit in the first place
    - Vector seems most suitable for that purpose
        - Entity should be able to store concurent status effect. If there are more - Vector takes care of reallocating it
    */

    //NOTE: Status effect should start ticking once entity enters the tree(is ready)
    if(StatusEffect *statusEffectInternal = get_registered_status_effect(status_effect_name))
    {
        if(StatusEffect* statusEffectAppliedInstance = target->get_status_effect(status_effect_name))
        {
            /*
            - If no buff with passed name is applied on entity, apply an instance of it.
            - If buff instance with passed name is applied on entity:
                - If buff is non-stackable: replace it with new instance
                - If buff is stackable: Add another stack to that buff instance
                    - and reset duration(maybe inside StatusEffect?)
            */


            statusEffectAppliedInstance->add_stacks(1);
        }
        else
        {
            StatusEffect* statusEffectInstance = statusEffectInternal->copy();
            statusEffectInstance->set_target(target);

            //target->applied_status_effects.append(statusEffectInstance);
            target->applied_status_effects.insert(statusEffectInstance->name, statusEffectInstance);
            //Effect is considered active when onApply() is called
            statusEffectInstance->on_apply();
        }
    }
    else
    {
        return nullptr;
    }
    //FIXME: Currently returns nullptr
    return nullptr;
}

void StatusEffectManager::load_data_from_directory()
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
            printf("%s\n", fileName.ascii().get_data());
            Error readErr = Error::OK;

            Ref<FileAccess> file = FileAccess::open(dir->get_current_dir()+"/"+fileName, FileAccess::READ);

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
                    String effectName = fileName.substr(0, fileName.length() - 6);

                    /**
                     * Check what logic should be tied to that status effect
                    */
                    String logicObjectName = effectName;

                    //Update registered status effect with default values
                    if(StatusEffect* statusEffectReg = get_registered_status_effect(effectName))
                    {
                        Dictionary data = Dictionary(json->get_data());

                        statusEffectReg->load_data(data);
                    }
                    else
                    {
                        //No such status effect - ignoring
                    }
                }
            }
        }
    }

    for(auto effectData : registered_status_effects)
    {
        /*
        printf("Registered effect name = %s\n", effectData.value->name.ascii().ptr());
        printf("%s\n", String(*(effectData.value->statusEffectData)).ascii().ptr());
        */
    }

}
