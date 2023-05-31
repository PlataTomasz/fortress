#if !defined(GAME_STRING_NAMES_H_INCLUDED)
#define GAME_STRING_NAMES_H_INCLUDED

#include <core/string/string_name.h>

class GameStringNames
{
private:
    static GameStringNames* singleton;
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

    GameStringNames();
};

#endif // GAME_STRING_NAMES_H_INCLUDED
