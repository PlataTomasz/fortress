#if !defined(GAME_STRING_NAMES_H_INCLUDED)
#define GAME_STRING_NAMES_H_INCLUDED

#include <core/string/string_name.h>

class GameStringNames
{
private:
    static GameStringNames* singleton;

    GameStringNames();
protected:
public:
    static GameStringNames* get_singleton()
    {
        if(!singleton)
        {
            singleton = memnew(GameStringNames);
        }
        return singleton;
    }

    StringName ENTITIES_GROUP;

    //Signals
    StringName ON_DAMAGE_TAKEN;
    StringName ON_DAMAGE_DEALT;
    StringName ON_ABILITY_HIT;
    StringName ON_ATTACK_HIT;
    StringName PRE_DEATH;
    StringName ON_DEATH;
    StringName ON_HEALTH_CHANGE;

    //Mercenaries
    StringName SWORD_MERCENARY;
};

#endif // GAME_STRING_NAMES_H_INCLUDED
