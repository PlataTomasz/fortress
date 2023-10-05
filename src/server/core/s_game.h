#if !defined(SERVER_GAME_INCLUDED)
#define SERVER_GAME_INCLUDED

//For some reason "#include <scene/main/node.h>" directly, fails - This is workaround
#include <scene/main/canvas_item.h>
#include <server/core/game_commands/s_game_commands.h>
#include "s_game_level.h"

#include "s_player.h"

class S_Game : public Node
{
GDCLASS(S_Game, Node);
private:
    //Array of all players in-game
    S_Player *players;
    //Game commands to be executed in the next frame
    List<S_GameCommand *> game_commands;

    void fixed_tick();
protected:
    void _notification(int notification);
public:
    void put_game_command(S_GameCommand *gamecmd);

    Error serialize_gamestate(uint8_t *data, uint64_t size);

    /**
     * @return Pointer to current map or nullptr if map is not set
    */
    S_GameLevel *get_current_level();
    S_Game();
};

#endif // SERVER_GAME_INCLUDED
