#include "client.hpp"
#include <scene/main/multiplayer_api.h>
#include <scene/scene_string_names.h>
#include <core/io/marshalls.h>
#include <shared/helper_macros.h>
#include <client/game.h>
#include <client/ui/user_interface.h>
#include <shared/entities/mercenaries/mercenary.hpp>

#include <shared/entities/entity.h>

#include <client/ui/main_menu.h>

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
}

void Client::_on_enter_tree() {
    DISABLE_IN_EDITOR();
    ERR_FAIL_NULL(scene_multiplayer);
    scene_multiplayer->set_root_path(get_path());

    SceneTree *scene_tree = get_tree();
    ERR_FAIL_NULL(scene_tree);
    scene_tree->set_multiplayer(scene_multiplayer, get_path());
    scene_multiplayer->set_auth_callback(callable_mp(this, &Client::auth_callback));
    scene_multiplayer->connect("peer_authenticating", callable_mp(this, &Client::_on_auth_start));
    scene_multiplayer->connect("peer_authentication_failed", callable_mp(this, &Client::_on_auth_fail));

    scene_multiplayer->connect("connected_to_server", callable_mp(this, &Client::_on_server_connect));
    scene_multiplayer->connect("server_disconnected", callable_mp(this, &Client::_on_server_disconnect));
}

void Client::_on_player_spawn(Player *p_player) {
    ERR_FAIL_NULL(scene_multiplayer);
    if (scene_multiplayer->get_unique_id() == p_player->get_owner_peer_id()) {
        //pla
    }
}

void Client::server_rpc_set_controlled_entity(String entity_name) {
    // Preconditions
    ERR_FAIL_NULL(game);
    GameLevel *game_level = game->get_current_level();
    ERR_FAIL_NULL(game_level);
    ERR_FAIL_NULL(player);

    // Entity is not YET spawned on client - We need to await the spawn somehow
    Mercenary *ent = Object::cast_to<Mercenary>(game->get_current_level()->get_entity(entity_name));
    if (!ent) {
        // Controlled entity might not yet spawned on client - Await spawn
        MultiplayerSpawner *spawner = game_level->get_entity_spawner();
        ERR_FAIL_NULL(spawner);

        Callable callable = callable_mp(this, &Client::_on_controlled_entity_spawn).bind(entity_name);

        spawner->connect("spawned", callable);
    } else {
        player->set_controlled_entity(ent);
    }
}

void Client::_on_controlled_entity_spawn(Entity *ent, const String& entity_name) {
    Mercenary *mercenary = Object::cast_to<Mercenary>(ent);
    ERR_FAIL_NULL(mercenary);
    if(mercenary->get_name() == entity_name) {
        player->set_controlled_entity(mercenary);
    }
}

void Client::_on_auth_start(int peer_id) {
    ERR_FAIL_NULL(scene_multiplayer);
    int len = 0;
    Error err = encode_variant(playerdata, nullptr, len, false, 0);
    ERR_FAIL_COND(err);

    PackedByteArray buffer;
    ERR_FAIL_COND(buffer.resize(len) != OK);
    ERR_FAIL_COND(encode_variant(playerdata, buffer.ptrw(), len, false, 0) != OK);
    ERR_FAIL_COND(scene_multiplayer->send_auth(peer_id, buffer) != OK);
}

void Client::_on_join_server_btn_press() {
    ERR_FAIL_NULL(user_interface);
    MainMenu *main_menu = user_interface->get_main_menu();
    ERR_FAIL_NULL(main_menu);
    String ip = main_menu->get_server_adress();
    int port = main_menu->get_server_port();

    playerdata["nickname"] = main_menu->get_choosen_nickname();
    playerdata["mercenary"] = main_menu->get_selected_mercenary();

    Error err = connect_to_game_server(ip, port);
    if(err == OK) {
        main_menu->set_visible(false);
    }
}

void Client::_init()
{
    client_peer.instantiate(); //Same as using memnew
    scene_multiplayer.instantiate();
}

void Client::_notification(int notification)
{
    DISABLE_IN_EDITOR();
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

        case NOTIFICATION_ENTER_TREE:
            _on_enter_tree();
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
    emit_signal("player_connected", player);
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

    MainMenu *main_menu = user_interface->get_main_menu();
    if(main_menu) {
        main_menu->set_visible(true);
    }

    player->cleanup_after_disconnect();
}

void Client::process()
{

}

Error Client::auth_callback(int peer_id, PackedByteArray p_data) {
    Variant var;
    Error data_err = decode_variant(var, p_data.ptr(), p_data.size());
    ERR_FAIL_COND_V_MSG(data_err != OK, data_err, "Received invalid auth data from server");
    ERR_FAIL_COND_V_MSG(var.get_type() != Variant::DICTIONARY, ERR_INVALID_DATA, "Received invalid auth data from server");

    Dictionary gameinfo = var.operator Dictionary();
    Variant var_level_name = gameinfo.get_valid("level");
    ERR_FAIL_COND_V_MSG(var_level_name.get_type() != Variant::STRING, ERR_INVALID_DATA, "Level name is malformed!" + itos(peer_id));

    //TODO: Proper level_name validation
    ERR_FAIL_COND_V_MSG(String(var_level_name) != String("Aram"), ERR_INVALID_DATA, "Invalid level name!");
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
    ClassDB::bind_method(D_METHOD("server_rpc_set_controlled_entity", "entity_name"), &Client::server_rpc_set_controlled_entity);

    ClassDB::bind_method(D_METHOD("get_player"), &Client::get_player);
    ClassDB::bind_method(D_METHOD("set_player", "player"), &Client::set_player);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "player"), "set_player", "get_player");

    ClassDB::bind_method(D_METHOD("get_user_interface"), &Client::get_user_interface);
    ClassDB::bind_method(D_METHOD("set_user_interface", "user_interface"), &Client::set_user_interface);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "user_interface", PROPERTY_HINT_NODE_TYPE, Control::get_class_static()), "set_user_interface", "get_user_interface");

    ADD_SIGNAL(MethodInfo("player_connected", PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_RESOURCE_TYPE, Player::get_class_static())));

    ClassDB::bind_method(D_METHOD("quit"), &Client::quit);
}

void Client::set_user_interface(UserInterface *new_user_interface) {
    user_interface = new_user_interface;

    DISABLE_IN_EDITOR();
    MainMenu *menu = user_interface->get_main_menu();
    if(menu) {
        menu->get_join_button()->connect("pressed", callable_mp(this, &Client::_on_join_server_btn_press));
    }
}

UserInterface *Client::get_user_interface() {
    return user_interface;
}

Client *Client::get_instance() {
    ERR_FAIL_NULL_V(SceneTree::get_singleton(), nullptr);
    ERR_FAIL_NULL_V(SceneTree::get_singleton()->get_root(), nullptr);

    Client *client_instance = Object::cast_to<Client>(SceneTree::get_singleton()->get_root()->get_node_or_null(NodePath("Client")));

    return client_instance;
}

void Client::disconnect_from_server() {
    ERR_FAIL_NULL(scene_multiplayer);
    scene_multiplayer->disconnect_peer(1);
}

void Client::quit() {
    ERR_FAIL_NULL(get_tree());
    get_tree()->quit();
}