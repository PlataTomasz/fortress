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

#include <core/core_bind.h>

class Game;
class ServerConsoleCommand;

/**
 * Server is a node responsible for managing connections, sending and handling data over network.
*/
class Server : public Realm
{
GDCLASS(Server, Realm);
private:
    HashMap<String, ServerConsoleCommand *> defined_console_commands;
    List<Pair<String, Array>> commands_to_execute;

    Ref<ENetMultiplayerPeer> server_peer;
    SceneMultiplayer *scene_multiplayer;

    HashMap<int, Ref<Player>> connected_players;

    Ref<core_bind::Thread> command_listening_thread;

    Node *players = nullptr;

    void _await_console_command();
    void _setup_console_commands();
protected:
    void _notification(int notification)
    {
        DISABLE_IN_EDITOR();
        switch (notification)
        {
            case NOTIFICATION_POSTINITIALIZE:
            {
                _init();
                break;
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
    void server_rpc_set_controlled_entity(String entity_name);
    
    Error auth_callback(int peer_id, PackedByteArray data);
    void _on_auth_start(int peer_id);
    void _on_auth_fail(int peer_id);
public:
    static Server *get_instance();
    //Returns player by peer_id, nullptr if no player has such peer
    Ref<Player> get_player(int peer_id);

    void add_player(int peer_id, Ref<Player> player);
    void remove_player(int peer_id);

    void _ready();

    void process();

    void disconnect_peer(int peer_id, const String reason = "Disconnected by server!");

    void add_console_command(const String& command_name, ServerConsoleCommand *command_object);

    Error execute_server_command(const String& command_name, PackedStringArray command_arguments);

    bool is_peer_connected(int peer_id);
 
    Server();
};


#endif // SERVER_INCLUDED