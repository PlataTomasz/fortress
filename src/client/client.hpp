#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <scene/main/node.h>

#include <modules/enet/enet_multiplayer_peer.h>
#include <shared/helpers/object_ptr.h>
#include <modules/multiplayer/scene_multiplayer.h>

class Game;
class UserInterface;

/**
 * Client is a node responsible for connecting to server, disconnecting, receiving and sending data to server
 * Client may have Server node in It's node hierarchy
*/
class Client : public Node
{
GDCLASS(Client, Node);
private:
    static Game *game;

    Ref<ENetConnection> connection;
    Ref<ENetMultiplayerPeer> client_peer;
    Ref<ENetMultiplayerPeer> server_peer;

    UserInterface *user_interface = nullptr;

    void on_connect();
    void on_disconnect();
    void _init();
public:
    void process();
    void ready();
    void enter_tree();
    Error connect_to_game_server(const String &ip, int port);
protected:
    void _notification(int notification);
    static void _bind_methods();
    void ready_signal()
    {
        print_line("Ready with signal!");
    };

public:
    static Game *get_game();

    Client();
    ~Client(){};
};

#endif // CLIENT_H_INCLUDED
