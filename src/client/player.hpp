#if !defined(PLAYER_HPP_INCLUDED)
#define PLAYER_HPP_INCLUDED

#include "entities/mercenaries/mercenary.hpp"
#include <modules/enet/enet_multiplayer_peer.h>

class Player
{
private:
    //Is camera free or attached to controlled entity
    bool freeCam;
    uint8_t id = 0;
    Ref<ENetPacketPeer> peer;

protected:
    static void _bind_methods(){};
public:
    /**
    * Entity the player is currently controlling.
    */
    Mercenary *controlledEntity;

    uint8_t get_id()
    {
        return id;
    }

    Ref<ENetPacketPeer> get_peer()
    {
        return peer;
    }



    Player();
    ~Player();
};

#endif // PLAYER_HPP_INCLUDED
