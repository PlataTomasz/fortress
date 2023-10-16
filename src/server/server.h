#if !defined(SERVER_INCLUDED)
#define SERVER_INCLUDED

#include <scene/main/node.h>
#include <modules/enet/enet_connection.h>
#include <scene/main/multiplayer_api.h>
#include <modules/enet/enet_multiplayer_peer.h>
#include <core/templates/hash_map.h>
#include <server/core/s_player.h>


#include <server/core/game_commands/s_game_command_factory.h>

/**
 * Server is a node responsible for managing connections, sending and handling data over network.
*/
class Server : public Node
{
GDCLASS(Server, Node);
public:
    
private:
    Ref<ENetConnection> connection;
    S_Game *game = nullptr;

    uint8_t player_count = 0;
    S_Player players[16];
    HashMap<Ref<ENetPacketPeer>, S_Player *> players_by_peer;

protected:
    void _notification(int notification)
    {
        switch (notification)
        {
            case NOTIFICATION_PROCESS:
            {
                process();
                break;
            }

            case NOTIFICATION_READY:
            {
                ready();
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
public:
    S_Player *get_player_by_peer(Ref<ENetPacketPeer> peer);
    Ref<ENetPacketPeer> get_peer_by_player_id(uint8_t p_player_id);

    void send_data_to_all(const uint8_t *packet_data, uint64_t size)
    {

        List<Ref<ENetPacketPeer>> peers;
        connection->get_peers(peers);
        for(Ref<ENetPacketPeer> peer : peers)
        {
            peer->put_packet(packet_data, size);
        }
    }

    void send_data(Ref<ENetPacketPeer> target, const uint8_t *packet_data, uint64_t size)
    {
        target->put_packet(packet_data, size);
    }

    void ready()
    {
        game = reinterpret_cast<S_Game*>(get_node(NodePath("Game")));

        int server_port = 7654;

        //Setup networking
        connection = Ref<ENetConnection>();
        connection.instantiate(); //Same as using memnew

        Error err = connection->create_host_bound((IPAddress)("*"), server_port, 32, 3);

        if(err == Error::OK)
        {
            print_line("Server is listening on port", server_port);
        }
        else
        {
            print_line("Failed to create server! Error code: " + err);
        }
    }

    void on_peer_connect(Ref<ENetPacketPeer> peer)
    {
        print_line("Connection initialized with ", peer, "Awaiting client info.");
    }

    void on_peer_disconnect(Ref<ENetPacketPeer> peer)
    {
        //NOTE: Might crash because use of get()?
        print_line("Player", players_by_peer.get(peer), "disconnected");
    }

    void on_receive(Ref<ENetPacketPeer> sender, const uint8_t *packet_data, uint64_t size);

    void process()
    {
        //Read incoming network data and schedule GameCmd to avoid blocking
        //multiplayer_peer->poll();

        //Parse ENet event
        ENetConnection::Event enet_event;

        switch (connection->service(0, enet_event))
        {
            case ENetConnection::EventType::EVENT_CONNECT:
            {
                on_peer_connect(enet_event.peer);
            }
            break;

            case ENetConnection::EventType::EVENT_DISCONNECT:
            {
                on_peer_disconnect(enet_event.peer);
            }
            break;

            case ENetConnection::EventType::EVENT_RECEIVE:
            {
                on_receive(enet_event.peer, enet_event.packet->data, enet_event.packet->dataLength);
            }
            break;
            
            default:
                break;
        }
    }

    S_Game *get_game();


    Server()
    {
        //Required, so that Node can tick
        set_process(true);
    }
};


#endif // SERVER_INCLUDED