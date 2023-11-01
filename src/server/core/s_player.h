#if !defined(SERVER_PLAYER_INCLUDED)
#define SERVER_PLAYER_INCLUDED

#include <core/string/ustring.h>
#include <core/object/ref_counted.h>
#include <core/io/resource.h>

class S_BaseEntity;

class S_Player : public Resource
{
GDCLASS(S_Player, Resource);
private:
    S_BaseEntity *controlled_entity = nullptr;

    uint8_t id = 0;
    
    String nickname = "unset";
protected:

public:
    void set_controlled_entity(S_BaseEntity *p_controlled_entity);
    S_BaseEntity *get_controlled_entity();

    void change_nickname(String nickname);
    String get_nickname();

    String get_choosen_mercenary()
    {
        return "TODO";
    }

    //Takes control of that player if he is not connected
    /*
    void set_controlling_peer(Ref<ENetPacketPeer> peer);
    Ref<ENetPacketPeer> get_controlling_peer();
    */

    S_Player(){};
};

#endif // SERVER_PLAYER_INCLUDED
