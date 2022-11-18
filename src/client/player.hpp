#if !defined(PLAYER_HPP_INCLUDED)
#define PLAYER_HPP_INCLUDED

#include "entities/mercenaries/mercenary.hpp"

class Player : public Node
{
private:
    //Is camera free or attached to controlled entity
    bool freeCam;

protected:
    static void _bind_methods(){};
public:
    /**
    * Entity the player is currently controlling.
    */
    Mercenary *controlledEntity;

    Player();
    ~Player();
};

#endif // PLAYER_HPP_INCLUDED
