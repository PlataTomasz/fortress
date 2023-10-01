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
    void send_packet_to_all()
    {

    }

    void send_packet(Ref<ENetPacketPeer> target)
    {

    }

    void ready()
    {
        int server_port = 7654;

        //Setup networking
        connection = Ref<ENetConnection>(memnew(ENetConnection));
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
        print_line("Connected ");
        String str = "wololo!";
        peer->put_packet(str.to_ascii_buffer().ptr(), str.to_ascii_buffer().size());
        //connection->put_packet(str.to_ascii_buffer().ptr(), str.to_ascii_buffer().size());

    }

    void on_peer_disconnect(Ref<ENetPacketPeer> peer)
    {
        print_line("Disconnected ");
        
    }

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
                const uint8_t *buffer = enet_event.packet->data;
                int buffer_size = enet_event.packet->dataLength;

                /*
                String str("[");
                for (int j = 0; j < buffer_size; j++) {
                    if (j > 0) {
                        str += ", ";
                    }

                    str += Variant(buffer[j]).operator String();
                }
                str += "]";
                */
                String str;
                str.parse_utf8(reinterpret_cast<const char*>(buffer), buffer_size);

                //print_line("Received data: ", str);
                //TODO: Pass received data to game
                SGameCommand(buffer, buffer_size);

            }
            break;
            
            default:
                break;
        }
    }


    Server()
    {
        set_process(true);
    }
};


#endif // SERVER_INCLUDED