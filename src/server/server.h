#if !defined(SERVER_INCLUDED)
#define SERVER_INCLUDED

#include <scene/main/node.h>
#include <modules/enet/enet_connection.h>
#include <scene/main/multiplayer_api.h>
#include <modules/enet/enet_multiplayer_peer.h>
#include <core/templates/hash_map.h>
#include <server/core/s_player.h>
#include <server/networking/requests/request_handler.h>

#include <modules/multiplayer/scene_multiplayer.h>

class S_Game;

/**
 * Server is a node responsible for managing connections, sending and handling data over network.
*/
class Server : public Node
{
GDCLASS(Server, Node);

private:
    Ref<ENetMultiplayerPeer> server_peer;
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
        //TODO: Replace with MultiplayerAPI
        /*
        server_peer->get_peers(peers);
        for(Ref<ENetPacketPeer> peer : peers)
        {
            peer->put_packet(packet_data, size);
        }
        */
    }

    void send_data(Ref<ENetPacketPeer> target, const uint8_t *packet_data, uint64_t size)
    {
        target->put_packet(packet_data, size);
    }

    void ready();

    void on_peer_connect(int peer_id)
    {
        print_line("Player", peer_id, "connected");
    }

    void on_peer_disconnect(int peer_id)
    {
        print_line("Player", peer_id, "disconnected");
    }

    void on_receive(Ref<ENetPacketPeer> sender, const uint8_t *packet_data, uint64_t size);

    void process()
    {
        //get_multiplayer()->get_multiplayer_peer()->poll();
        //print_error("- _ -");
    }

    S_Game *get_game();


    Server()
    {
        //Required, so that Node can tick
        set_process(true);
    }
};


#endif // SERVER_INCLUDED