#include "status_effect_manager.hpp"
#include <core/io/dir_access.h>
#include <core/io/json.h>

#include "mercenaries/tundra/tundra_spiky_ball.hpp"

StatusEffectManager::StatusEffectManager()
{
    //Path where all deafult status effects are stored
    String defaultStatusEffectPath = "resources/status_effects";

    //Register StatusEffectBehaviour codes
    statusEffectScripts = new StatusEffectScript*[StatusEffectScriptID::STATUS_EFFECT_SCRIPT_ID_MAX]();

    //Empty scripts - used mostly for StatusEffects that don't do any logic
    statusEffectScripts[StatusEffectScriptID::NONE] = new StatusEffectScript();
    statusEffectScripts[StatusEffectScriptID::TUNDRA_SPIKY_BALL] = statusEffectScripts[StatusEffectScriptID::NONE];


    loadFromDirectory();
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
    const String name = statusEffect->statusEffectData->name;

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

StatusEffect *StatusEffectManager::getStatusEffect(String statusEffectName)
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

bool StatusEffectManager::removeStatusEffect(String statusEffectName, Entity *target)
{
    return target->statusEffects.erase(statusEffectName);
}

StatusEffect *StatusEffectManager::applyStatusEffect(String statusEffectName, float durration, Entity *target, Entity *inflictor)
{
    //NOTE: Status effect should start ticking once entity enters the tree(is ready)
    if(StatusEffect *statusEffectInternal = getStatusEffect(statusEffectName))
    {
        StatusEffect *statusEffect;

        target->statusEffects.insert(statusEffectName, statusEffect);

        return statusEffect;
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

                    String tooltip = jsonData.get("tooltip", "game_tooltip_" + effectName);

                    printf("EffectName = %s\n", effectName.ascii().ptr());

                    //If type is invalid 0 is set instead
                    int maxStacks = int(jsonData.get("maxStacks", 5));
                    int damage = int(jsonData.get("damage", 5));
                    int secondsDuration = int(jsonData.get("duration", 5));
                    //TODO: Get process frames per second from somewhere
                    int duration = secondsDuration*60;

                    int scriptID = int(jsonData.get("scriptId", StatusEffectScriptID::NONE));

                    if( !(scriptID >= 0 || scriptID < STATUS_EFFECT_SCRIPT_ID_MAX))
                    {
                        //Log warning that no logic is attached to StatusEffect because of invalid ID
                        scriptID = StatusEffectScriptID::NONE;
                    }

                    /**
                     * Check what logic should be tied to that status effect
                    */
                    String logicObjectName = effectName;

                    printf("Damage = %d\n", damage);
                    printf("Duration = %d\n", duration);

                    StatusEffectData *statusEffectData = new StatusEffectData(
                        effectName,
                        effectName,
                        tooltip,
                        maxStacks,
                        duration,
                        damage
                    );
                    StatusEffect *statusEffect = new StatusEffect(statusEffectData, statusEffectScripts[scriptID]);




                    registerStatusEffect(statusEffect);

                    printf("Size registered effects: %d\n", registeredStatusEffects.size());

                }
            }
        }
    }

    for(auto effectData : registeredStatusEffects)
    {
        printf("Registered effect name = %s\n", effectData.value->statusEffectData->name.ascii().ptr());
        printf("%s\n", String(*(effectData.value->statusEffectData)).ascii().ptr());        
    }

}