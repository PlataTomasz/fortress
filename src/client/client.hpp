#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <scene/main/node.h>

#include <modules/enet/enet_multiplayer_peer.h>
#include <shared/helpers/object_ptr.h>
#include <server/server.h>


/**
 * Client is a node responsible for connecting to server, disconnecting, receiving and sending data to server
 * Client may have Server node in It's node hierarchy
*/
class Client : public Node
{
GDCLASS(Client, Node);
private:
    Ref<ENetConnection> connection;
    Ref<ENetPacketPeer> peer;

    void on_connect();
    void on_disconnect();
    void on_receive(const uint8_t *packet_data, uint64_t size);
public:
    void process();
    void ready();
    void enter_tree();
    Error connect_to_game_server(const String &ip, int port);
    void send_data_to_server(const uint8_t *packet_data, uint64_t packet_size);
    /**
     * Creates game server embedded in client - Simillar to GMod and CSGO
     * If server is already working, It is shut down and recreated with passed arguments
    */
    ObjectPtr<Server> create_local_game_server();
    void send_data();
    //void send_game_cmd(const GameCommand& game_cmd);
protected:
    void _notification(int notification);
    static void _bind_methods();
    void ready_signal()
    {
        print_line("Ready with signal!");
    };

public:
    Client();
    ~Client(){};
};

#endif // CLIENT_H_INCLUDED
