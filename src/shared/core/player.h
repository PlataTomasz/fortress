#if !defined(PLAYER_INCLUDED)
#define PLAYER_INCLUDED

#include <core/string/ustring.h>
#include <core/object/ref_counted.h>
#include <core/io/resource.h>

class Entity;

class Player : public Resource
{
GDCLASS(Player, Resource);
private:
    Entity *controlled_entity = nullptr;

    uint8_t id = 0;

    int owner_peer_id = 0;
    
    String nickname = "unset";
protected:

public:
    void set_controlled_entity(Entity *p_controlled_entity);
    Entity *get_controlled_entity();

    void change_nickname(String nickname);
    String get_nickname();

    int get_owner_peer_id(){return owner_peer_id;};
    void set_owner_peer_id(int peer_id){owner_peer_id = peer_id;};

    //TODO
    String get_choosen_mercenary()
    {
        return "TODO";
    }

    //Takes control of that player if he is not connected
    /*
    void set_controlling_peer(Ref<ENetPacketPeer> peer);
    Ref<ENetPacketPeer> get_controlling_peer();
    */

    Player(){};
};

#endif //PLAYER_INCLUDED
