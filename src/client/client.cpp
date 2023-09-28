#include "client.hpp"
#include <scene/main/multiplayer_api.h>

Client::Client()
{
    
}

Error Client::connect_to_game_server(const String &ip, int port)
{
    return multiplayer_peer->create_client(ip, port, 3);
}

void Client::ready()
{
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
    return new Server();
}

void Client::enter_tree()
{

}

void Client::process()
{
    //Receive data from server

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