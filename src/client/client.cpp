#include "client.hpp"
#include <scene/main/multiplayer_api.h>
#include <shared/io/byte_reader.h>
#include <scene/scene_string_names.h>
#include <shared/helper_macros.h>
#include <client/game.hpp>
#include <client/ui/user_interface.h>

Game *Client::game = nullptr;

Client::Client()
{
    DISABLE_IN_EDITOR();
    set_process(true);
}

Error Client::connect_to_game_server(const String &ip, int port) {
	Error err = server_peer->create_client(ip, port);
	if (err == OK) {
        // Previous game clean-up
        if (game) {
           game->queue_free();
           server_peer->close();
        }
        // Create Game object
        game = memnew(Game);
        game->set_name("Game");
        add_child(game);
	}
    return err;
}

Game *Client::get_game()
{
    return game;
}

void Client::ready()
{
    DISABLE_IN_EDITOR();

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
    //Create UI
    user_interface = memnew(UserInterface);
    user_interface->set_name("UserInterface");
    add_child(user_interface);
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

void Client::process()
{

}

void Client::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("connect_to_game_server", "ip", "port"), &Client::connect_to_game_server);
}