#include "client.hpp"
#include <scene/main/multiplayer_api.h>
#include <shared/io/byte_reader.h>
#include <scene/scene_string_names.h>
#include <shared/helper_macros.h>
#include <client/game.h>
#include <client/ui/user_interface.h>
#include <shared/entities/mercenaries/mercenary.hpp>

Client::Client()
{
    DISABLE_IN_EDITOR();
    set_process(true);
    player.instantiate();
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
    
    scene_multiplayer.instantiate();
    scene_multiplayer->set_root_path(get_path());
    get_tree()->set_multiplayer(scene_multiplayer, get_path());
    scene_multiplayer->set_auth_callback(callable_mp(this, &Client::auth_callback));
    scene_multiplayer->connect("peer_authenticating", callable_mp(this, &Client::_on_auth_start));
    scene_multiplayer->connect("peer_authentication_failed", callable_mp(this, &Client::_on_auth_fail));

    scene_multiplayer->connect("connected_to_server", callable_mp(this, &Client::_on_server_connect));
    scene_multiplayer->connect("server_disconnected", callable_mp(this, &Client::_on_server_disconnect));
}

void Client::_on_auth_start(int peer_id) {
    Dictionary playerdata;
    playerdata["nickname"] = player->get_nickname();
    playerdata["mercenary"] = player->get_choosen_mercenary();

    int len = 0;
    Error err = encode_variant(playerdata, nullptr, len, false, 0);
    ERR_FAIL_COND(err);

    PackedByteArray buffer;
    buffer.resize(len);

    encode_variant(playerdata, buffer.ptrw(), len, false, 0);

    scene_multiplayer->send_auth(peer_id, buffer);
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
    print_line("Player", player->get_nickname(), "joined the server!");
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

Error Client::auth_callback(int peer_id, PackedByteArray data) {
    Variant var;
    Error data_err = decode_variant(var, data.ptr(), data.size());
    ERR_FAIL_COND_V_MSG(data_err != OK, data_err, "Received invalid auth data from server");
    ERR_FAIL_COND_V_MSG(var.get_type() != Variant::DICTIONARY, ERR_INVALID_DATA, "Received invalid auth data from server");

    Dictionary gameinfo = var.operator Dictionary();
    Variant var_level_name = gameinfo.get_valid("level");
    ERR_FAIL_COND_V_MSG(var_level_name.get_type() != Variant::STRING, ERR_INVALID_DATA, "Level name is malformed!" + itos(peer_id));

    //TODO: Proper level_name validation
    ERR_FAIL_COND_V_MSG(String(var_level_name) != String("ExampleGameLevel"), ERR_INVALID_DATA, "Invalid level name!");
    game = memnew(Game);
    game->set_name("Game");
    add_child(game);

    game->load_game_level(var_level_name);
    game->setup_game();

    print_line("Auth succeeded on client");
    scene_multiplayer->complete_auth(peer_id);
    return OK;
}

void Client::_on_auth_fail(int peer_id) {
    print_error("Authentication with server failed!");
    // Display disconnect popup
}

void Client::server_rpc_disconnect(const String reason) {
    // Return to main menu and display information about why this peer was disconnected by server
    print_line("You have been disconnected from server. Reason: " + reason);
}

void Client::set_player(Ref<Player> p_player) {
    player = p_player;
}

Ref<Player> Client::get_player() {
    return player;
}

void Client::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_peer"), &Client::get_peer);
    ClassDB::bind_method(D_METHOD("connect_to_game_server", "ip", "port"), &Client::connect_to_game_server);
    // RPC
    ClassDB::bind_method(D_METHOD("server_rpc_disconnect"), &Client::server_rpc_disconnect);

    ClassDB::bind_method(D_METHOD("get_player"), &Client::get_player);
    ClassDB::bind_method(D_METHOD("set_player", "player"), &Client::set_player);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "player"), "set_player", "get_player");
}