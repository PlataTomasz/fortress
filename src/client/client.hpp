#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <scene/main/node.h>

#include <modules/enet/enet_multiplayer_peer.h>
#include <shared/helpers/object_ptr.h>
#include <modules/multiplayer/scene_multiplayer.h>
#include <shared/core/realm.h>

#include <core/object/ref_counted.h>
#include <shared/core/player.h>

class Game;
class UserInterface;

/**
 * Client is a node responsible for connecting to server, disconnecting, receiving and sending data to server
 * Client may have Server node in It's node hierarchy
*/
class Client : public Realm
{
GDCLASS(Client, Realm);
private:
    Ref<ENetConnection> connection;
    Ref<ENetMultiplayerPeer> client_peer;
    Ref<SceneMultiplayer> scene_multiplayer;

    UserInterface *user_interface = nullptr;

    // Clientside player object
    Ref<Player> player;

    void _on_server_connect();
    void _on_server_disconnect();
    void _init();
    //RPC
    void server_rpc_disconnect(const String reason);

    void _on_auth_start(int peer_id);
    void _on_auth_fail(int peer_id);
    Error auth_callback(int peer_id, PackedByteArray data);
public:
    void process();
    void ready();
    void enter_tree();
    Error connect_to_game_server(const String &ip, int port);

    void set_player(Ref<Player> p_player);
    Ref<Player> get_player();
protected:
    void _notification(int notification);
    static void _bind_methods();

    Ref<ENetMultiplayerPeer> get_peer();
public:
    Client();
    ~Client(){};
};

#endif // CLIENT_H_INCLUDED
