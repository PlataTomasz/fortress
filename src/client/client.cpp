#include "client.hpp"
#include <scene/main/multiplayer_api.h>
#include <shared/io/byte_reader.h>
#include <scene/scene_string_names.h>
#include <shared/helper_macros.h>
#include <client/game.h>
#include <client/ui/user_interface.h>

Client::Client()
{
    DISABLE_IN_EDITOR();
    set_process(true);
}

Ref<ENetMultiplayerPeer> Client::get_peer() {
    return client_peer;
}

Error Client::connect_to_game_server(const String &ip, int port) {
	Error err = client_peer->create_client(ip, port);
	if (err == OK) {
        scene_multiplayer->set_multiplayer_peer(client_peer);
	}
	return err;
}

void Client::ready()
{
    DISABLE_IN_EDITOR();
    
    //client_peer->create_client("localhost", 7654);
    
    
    scene_multiplayer.instantiate();
    scene_multiplayer->set_root_path(get_path());
    get_tree()->set_multiplayer(scene_multiplayer, get_path());
    /*
    Ref<SceneMultiplayer> scene_multiplayer;
    scene_multiplayer.instantiate();
    scene_multiplayer->set_root_path(get_path());
    scene_multiplayer->set_multiplayer_peer(client_peer);
    get_tree()->set_multiplayer(scene_multiplayer, get_path());
    */

    scene_multiplayer->connect("connected_to_server", callable_mp(this, &Client::_on_server_connect));
    scene_multiplayer->connect("server_disconnected", callable_mp(this, &Client::_on_server_disconnect));
}

void Client::_init()
{
    client_peer = Ref<ENetMultiplayerPeer>();
    client_peer.instantiate(); //Same as using memnew

    //Create UI
    user_interface = memnew(UserInterface);
    user_interface->set_name("UserInterface");
    add_child(user_interface);


}

void Client::update_join_state(JoinState join_state) {
    
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

void Client::_on_server_connect()
{
    print_line("Connected to server. Sending playerdata");
    Dictionary playerdata;
    //playerdata["nickname"] = player->get_nickname();
    playerdata["nickname"] = "Nickname-01";
    //playerdata["mercenary"] = player->get_choosen_mercenary();
    playerdata["mercenary"] = "mercenary";

    rpc_id(0, "client_rpc_playerdata", playerdata);
}

void Client::_on_server_disconnect()
{
    print_line("Disconnected!");

    // Cleanup game object - We will create new one one next connect attempt
    if (game) { 
        remove_child(game);
        game->queue_free();
        game = nullptr;
    }
}

void Client::process()
{

}

void Client::client_rpc_playerdata(Dictionary playerdata) {
    
}

void Client::server_rpc_gameinfo(Dictionary gameinfo) {
    Variant level_name = gameinfo.get_valid("level");

    // Validation
    if (level_name.get_type() == Variant::STRING ) {
        
        // Clean-up previous game object
        if (game) {
            remove_child(game);
            game->queue_free();
            game = nullptr;
        }
        // Load level with that name
        //FIXME: Loading file like this asks for exploit that allows opening any file on host
        //Create new game object
        game = memnew(Game);
        game->set_name("Game");
        add_child(game);
        
        game->load_game_level(String(level_name));
        game->setup_game();

        print_line("Player", player->get_nickname(), "joined the server!");
    } else {
		//Invalid gameinfo - What to do now?
		print_error("Invalid gameinfo received from server!");
    }
}

void Client::server_rpc_disconnect(const String reason) {
    // Return to main menu and display information about why this peer was disconnected by server
    print_line("You have been disconnected from server. Reason: " + reason);
}

void Client::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_peer"), &Client::get_peer);
    ClassDB::bind_method(D_METHOD("connect_to_game_server", "ip", "port"), &Client::connect_to_game_server);
    // RPC
    ClassDB::bind_method(D_METHOD("client_rpc_playerdata"), &Client::client_rpc_playerdata);
    ClassDB::bind_method(D_METHOD("server_rpc_disconnect"), &Client::server_rpc_disconnect);
    ClassDB::bind_method(D_METHOD("server_rpc_gameinfo", "gameinfo"), &Client::server_rpc_gameinfo);
}