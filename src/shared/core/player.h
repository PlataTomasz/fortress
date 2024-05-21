#if !defined(PLAYER_INCLUDED)
#define PLAYER_INCLUDED

#include <core/string/ustring.h>
#include <core/object/ref_counted.h>
#include <core/io/resource.h>

class Mercenary;

class Player : public RefCounted
{
GDCLASS(Player, RefCounted);
private:
    Mercenary *controlled_entity = nullptr;

    int owner_peer_id = 0;
    
    String nickname = String("unset");
    // What mercenary was picked by this player? Initial one
    String choosen_mercenary = String("none");
protected:
    static void _bind_methods();
public:
    void set_controlled_entity(Mercenary *p_controlled_entity);
    Mercenary *get_controlled_entity();

    void change_nickname(const String nickname);
    String get_nickname();

    int get_owner_peer_id(){return owner_peer_id;};
    void set_owner_peer_id(int peer_id){owner_peer_id = peer_id;};

    String get_choosen_mercenary()
    {
        return choosen_mercenary;
    }

    void set_choosen_mercenary(const String& mercenary_name) {
        choosen_mercenary = mercenary_name;
    }

    //Takes control of that player if he is not connected
    /*
    void set_controlling_peer(Ref<ENetPacketPeer> peer);
    Ref<ENetPacketPeer> get_controlling_peer();
    */

    Player(){};
};

#endif //PLAYER_INCLUDED
