#if !defined(SERVER_GAME_INCLUDED)
#define SERVER_GAME_INCLUDED

//For some reason "#include <scene/main/node.h>" directly, fails - This is workaround
#include <scene/main/canvas_item.h>
#include "s_player.h"

class SGameLevel;

class SGame : public Node
{
private:
    //Array of all players in-game
    SPlayer *players;
    List<SGameCommand> game_commands;
protected:
    
public:
    /**
     * @return Pointer to current map or nullptr if map is not set
    */
    SGameLevel *get_current_level();
    SGame();
};

#endif // SERVER_GAME_INCLUDED
