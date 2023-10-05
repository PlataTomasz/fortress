#include "client.hpp"
#include <scene/main/multiplayer_api.h>
#include <shared/io/byte_reader.h>

Client::Client()
{
    set_process(true);
}

Error Client::connect_to_game_server(const String &ip, int port)
{
    peer = connection->connect_to_host(ip, port, 3);
    print_line("Peer ptr: ", peer.ptr());

    return Error::OK;
}

void Client::ready()
{
    connection.instantiate();
    connection->create_host(1, 3);

    connect_to_game_server("localhost", 7654);

    /*
    //Initialize networking

    multiplayer_peer = Ref<ENetMultiplayerPeer>(memnew(ENetMultiplayerPeer));
    Error connection_err = connect_to_game_server("localhost", 7654);

    print_line(multiplayer_peer->get_connection_status());

    if(connection_err == Error::OK)
    {
        Ref<MultiplayerAPI> multiplayer_api = MultiplayerAPI::create_default_interface();
        multiplayer_api->set_multiplayer_peer(multiplayer_peer);
        this->get_tree()->set_multiplayer(multiplayer_api, NodePath("/Client"));

        String str = "From client";
        PackedByteArray packet_data = str.to_ascii_buffer();

        multiplayer_peer->put_packet(packet_data.ptr(), packet_data.size());
    }
    else
    {
        print_error("Failed to connect to server! Error code: " + connection_err);
    }
    */
    
}

void Client::_notification(int notification)
{
    switch (notification)
    {
        case NOTIFICATION_PROCESS:
        {
            process();
        }
        break;

        case NOTIFICATION_READY:
        {
            ready();
        }
        break;
    
        default:
            break;
    }
}

ObjectPtr<Server> Client::create_local_game_server()
{
    Server *server = memnew(Server);

    return server;
}

void Client::enter_tree()
{

}

void Client::on_connect()
{
    print_line("Connected!");
}

void Client::on_disconnect()
{
    print_line("Disconnected!");
}

void Client::on_receive(const uint8_t *packet_data, uint64_t size)
{
    print_line("Received data from server!");
    //Handle data from server
    //HACK: Enet defines data pointer as const, but marshals methods require non const pointer, even though no write occurs
    ByteReader bytes(const_cast<uint8_t *>(packet_data), size);
    print_line(bytes.operator String());
}

void Client::process()
{
    //Receive data from server
    //Parse ENet event
        ENetConnection::Event enet_event;

        switch (connection->service(0, enet_event))
        {
            case ENetConnection::EventType::EVENT_CONNECT:
            {
                on_connect();
            }
            break;

            case ENetConnection::EventType::EVENT_DISCONNECT:
            {
                on_disconnect();
            }
            break;

            case ENetConnection::EventType::EVENT_RECEIVE:
            {
                on_receive(enet_event.packet->data, enet_event.packet->dataLength);
            }
            break;
            
            default:
                break;
        }
}

void Client::_bind_methods()
{
    //ClassDB::bind_method(D_METHOD("_process"), &Client::_process);
    /*
    ClassDB::bind_method(D_METHOD("get_class"), &Client::get_class);
    ClassDB::bind_method(D_METHOD("_ready"), &Client::_ready);
    ClassDB::bind_method(D_METHOD("_enter_tree"), &Client::_enter_tree);
    */
}