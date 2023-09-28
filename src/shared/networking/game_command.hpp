
#if !defined(GAME_COMMAND_INCLUDED)
#define GAME_COMMAND_INCLUDED

#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <core/io/marshalls.h>


/**
 * Class responsible for holding data regarding different game events, serialization, deserialization and validation in preparation to be sent to/received from server
*/
class GameCommand
{
public:
    enum CmdType
    {
        UNSPECIFIED = 0,
        MOVEMENT,
        BASIC_ATTACK,
        CAST_ABILITY,
        LEVEL_UP_ABILITY,
        STAT_CHANGE,
        MATCH_SCORE_CHANGE,
        KDA_CHANGE,
        CHAT_MSG,
    };
private:
    CmdType type;
    Vector3 target_position;
protected:

public:
    PackedByteArray to_byte_array()
    {
        PackedByteArray bytes;
        


        //Alloc memory
    }

    GameCommand()
    {

    }

    GameCommand()
    {

    }
};

#endif // GAME_COMMAND_INCLUDED