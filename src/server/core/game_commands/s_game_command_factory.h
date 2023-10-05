#if !defined(S_GAME_COMMAND_FACTORY_INCLUDED)
#define S_GAME_COMMAND_FACTORY_INCLUDED

#include <core/variant/variant.h>
#include "s_game_commands.h"

class SGameCommandFactory
{
public:
    enum SGameCommandType
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

    static S_GameCommand *create(const uint8_t *data, uint64_t size);
    static S_GameCommand *create(PackedByteArray data);
};

#endif // S_GAME_COMMAND_FACTORY_INCLUDED
