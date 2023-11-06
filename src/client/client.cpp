#include "client.hpp"
#include <scene/main/multiplayer_api.h>
#include <shared/io/byte_reader.h>
#include <scene/scene_string_names.h>
#include <shared/helper_macros.h>

Client::Client()
{
    DISABLE_IN_EDITOR();
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
    server_peer = Ref<ENetMultiplayerPeer>();
    server_peer.instantiate(); //Same as using memnew
    Ref<SceneMultiplayer> scene_multiplayer;
    scene_multiplayer.instantiate();
        
    Error err = server_peer->create_client("localhost", 7654);

    if (err)
    {
        print_error("Failed to connect to server! Error code: " + err);
    }
    else
    {
        on_connect();
    }

    scene_multiplayer->set_multiplayer_peer(server_peer);
    scene_multiplayer->set_root_path(get_path());
    get_tree()->set_multiplayer(scene_multiplayer, get_path());
    
}

void Client::_init()
{

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

        case NOTIFICATION_POSTINITIALIZE:
        {
            _init();
        }
        break;
    
        default:
            break;
    }
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

}

void Client::send_data_to_server(const uint8_t *packet_data, uint64_t packet_size)
{
    //TODO: Check if client is connected to server
    
    //NOTE: put_packet always send reliable packets, which may not be desired
    peer->put_packet(packet_data, packet_size);
}

void Client::_bind_methods()
{
    
}