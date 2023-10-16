#if !defined(SERVER_PLAYER_INCLUDED)
#define SERVER_PLAYER_INCLUDED

#include <core/string/ustring.h>
#include <enet/enet.h>
#include <core/object/ref_counted.h>
#include <modules/enet/enet_packet_peer.h>

class S_BaseEntity;

class S_Player
{
private:
    S_BaseEntity *controlled_entity = nullptr;

    uint8_t id = 0;
    Ref<ENetPacketPeer> peer;
    String nickname = "unset";
protected:

public:
    void set_controlled_entity(S_BaseEntity *p_controlled_entity);
    S_BaseEntity *get_controlled_entity();

    void change_nickname(String nickname);
    String get_nickname();

    //Takes control of that player if he is not connected
    void set_controlling_peer(Ref<ENetPacketPeer> peer);
    Ref<ENetPacketPeer> get_controlling_peer();


    S_Player(){};
};

#endif // SERVER_PLAYER_INCLUDED
