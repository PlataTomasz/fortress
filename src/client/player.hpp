#if !defined(PLAYER_HPP_INCLUDED)
#define PLAYER_HPP_INCLUDED

#include "entities/entity.hpp"

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
    Entity *controlledEntity;

    Player();
    ~Player();
};

#endif // PLAYER_HPP_INCLUDED
