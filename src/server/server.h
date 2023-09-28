#if !defined(SERVER_INCLUDED)
#define SERVER_INCLUDED

#include <scene/main/node.h>
#include <modules/enet/enet_connection.h>
#include <scene/main/multiplayer_api.h>
#include <modules/enet/enet_multiplayer_peer.h>

/**
 * Server is a node responsible for managing connections, sending and handling data over network.
*/
class Server : public Node
{
GDCLASS(Server, Node);
private:
    Ref<ENetConnection> connection;
    //Server peer
    Ref<ENetMultiplayerPeer> multiplayer_peer;
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

            default:
                break;
        }
    }
public:
    void ready()
    {
        int server_port = 7654;

        //Setup networking
        multiplayer_peer = Ref<ENetMultiplayerPeer>(memnew(ENetMultiplayerPeer));
        Error err = multiplayer_peer->create_server(server_port, 32, 3);

        multiplayer_peer->connect("peer_connected", callable_mp(this, &Server::on_peer_connect));
        multiplayer_peer->connect("peer_disconnected", callable_mp(this, &Server::on_peer_disconnect));

        if(err == Error::OK)
        {
            Ref<MultiplayerAPI> multiplayer_api = MultiplayerAPI::create_default_interface();
            multiplayer_api->set_multiplayer_peer(multiplayer_peer);

            this->get_tree()->set_multiplayer(multiplayer_api, NodePath("/Client/Server"));
            print_line("Server is listening on port", server_port);
        }
        else
        {
            print_line("Failed to create server! Error code: " + err);
        }
    }

    void on_peer_connect(int id)
    {
        print_line("Connected ", id);
        multiplayer_peer->set_target_peer(MultiplayerPeer::TARGET_PEER_BROADCAST);
    }

    void on_peer_disconnect(int id)
    {
        print_line("Disconnected ", id);
    }

    void process()
    {
        //Read incoming network data and schedule GameCmd to avoid blocking
        //multiplayer_peer->poll();



        String str = "wololo!";
        multiplayer_peer->put_packet(str.to_ascii_buffer().ptr(), str.to_ascii_buffer().size());

        if(int packet_count = multiplayer_peer->get_available_packet_count() > 0)
        {
            for(int i = 0;i<packet_count;i++)
            {
                const uint8_t *buffer;
                int buffer_size;

                multiplayer_peer->get_packet(&buffer, buffer_size);

                String str("[");
                for (int j = 0; j < buffer_size; j++) {
                    if (j > 0) {
                        str += ", ";
                    }

                    str += Variant(buffer[j]).operator String();
                }
                str += "]";

                print_line("Received data: ", str);
                //TODO: Add new game event to queue here
            }
        }
    }


    Server()
    {
        set_process(true);
    }
};


#endif // SERVER_INCLUDED