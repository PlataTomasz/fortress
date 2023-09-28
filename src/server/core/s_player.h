#if !defined(SERVER_PLAYER_INCLUDED)
#define SERVER_PLAYER_INCLUDED

#include <core/string/ustring.h>
#include <enet/enet.h>

class Entity;

class SPlayer
{
private:
    Entity *controlled_entity = nullptr;
    ENetPeer *peer = nullptr;
    String nickname;
protected:

public:
    void set_controlled_entity(Entity *ent);
    Entity *get_controlled_entity();

    void change_nickname(String nickname);
    String get_nickname();

    //Takes control of that player if he is not connected
    void set_controlling_peer(ENetPeer *peer);

};

#endif // SERVER_PLAYER_INCLUDED
