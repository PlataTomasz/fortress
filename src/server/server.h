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

#include <shared/core/realm.h>

class Game;

/**
 * Server is a node responsible for managing connections, sending and handling data over network.
*/
class Server : public Realm
{
GDCLASS(Server, Realm);
private:
    Ref<ENetMultiplayerPeer> server_peer;
    SceneMultiplayer *scene_multiplayer;

    HashMap<int, Ref<Player>> connected_players;

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
    
    void _on_peer_connect(int peer_id);
    void _on_peer_disconnect(int peer_id);

    static void _bind_methods();

    //RPC
    void server_rpc_disconnect(const String reason);
    void server_rpc_gameinfo(Dictionary p_gameinfo);
    void client_rpc_playerdata(Dictionary playerdata);

public:
    //Returns player by peer_id, nullptr if no player has such peer
    Ref<Player> get_player(int peer_id);

    void add_player(int peer_id, Ref<Player> player);

    void _ready();

    void process();

    void disconnect_peer(int peer_id, const String reason = "Disconnected by server!");

    Server();
};


#endif // SERVER_INCLUDED