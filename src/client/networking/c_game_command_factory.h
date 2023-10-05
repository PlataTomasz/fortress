#if !defined(C_GAME_COMMAND_FACTORY_INCLUDED)
#define C_GAME_COMMAND_FACTORY_INCLUDED

#include <core/variant/variant.h>
#include "c_game_commands.h"

class C_GameCommandFactory
{
public:
    enum C_GameCommandType
    {
        //Rejected unless handled by mods
        UNSPECIFIED = 0,
        //Indicates that packet contains a lot of game commands inside
        COMPRESSSED,
        //Both client and server can send this type of commands
        MOVEMENT,
        BASIC_ATTACK,
        CAST_ABILITY,
        //Client send only
        CHAT_MSG,
        //Server send only
        LEVEL_UP_ABILITY,
        STAT_CHANGE,
        MATCH_SCORE_CHANGE,
        KDA_CHANGE,

        CMD_TYPE_MAX
    };

    static C_GameCommand *create(const uint8_t *data, uint64_t size);
    static C_GameCommand *create(PackedByteArray data);
};

#endif // C_GAME_COMMAND_FACTORY_INCLUDED
