#if !defined(SERVER_INCLUDED)
#define SERVER_INCLUDED

#include <scene/main/node.h>
#include <modules/enet/enet_connection.h>
#include <scene/main/multiplayer_api.h>
#include <modules/enet/enet_multiplayer_peer.h>
#include <core/templates/hash_map.h>
#include <shared/core/player.h>

#include <modules/multiplayer/scene_multiplayer.h>
#include <shared/helpers/object_ptr.h>
#include <shared/helper_macros.h>

class Game;

/**
 * Server is a node responsible for managing connections, sending and handling data over network.
*/
class Server : public Node
{
GDCLASS(Server, Node);

private:
    Ref<ENetMultiplayerPeer> server_peer;

    ObjectPtr<SceneMultiplayer> scene_multiplayer;

    static ObjectPtr<Game> game;

    uint8_t max_player_count = 10;
    uint8_t current_player_count = 0;
    Player players[16];
    HashMap<Ref<ENetPacketPeer>, Player *> players_by_peer;
    
protected:
    void _notification(int notification)
    {
        DISABLE_IN_EDITOR();
        switch (notification)
        {
            case NOTIFICATION_POSTINITIALIZE:
            {
                _init();
            }

            case NOTIFICATION_PROCESS:
            {
                process();
                break;
            }

            case NOTIFICATION_READY:
            {
                _ready();
                break;
            }

            /*
            //BUG: Node is deleted anyways
            case NOTIFICATION_PREDELETE:
            {
                cancel_free();
                String err = "Node {} refuses to be deleted!";
                err.format(this);
                print_error(err);
            }
            break;
            */
            default:
                break;
        }
    }

    void _init();
public:
    Player *get_player_by_peer(Ref<ENetPacketPeer> peer);
    Ref<ENetPacketPeer> get_peer_by_player_id(uint8_t p_player_id);

    void _ready();

    void on_peer_connect(int peer_id);
   
    void on_peer_disconnect(int peer_id);

    void process()
    {

    }

    static ObjectPtr<Game> get_game();

    Server();
};


#endif // SERVER_INCLUDED