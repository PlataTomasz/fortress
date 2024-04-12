#include "sh_game.h"
#include <server/server.h>
#include <shared/helper_macros.h>
#include <shared/entities/living_entity.h>
#include <scene/scene_string_names.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <scene/resources/packed_scene.h>
#include <scene/main/node.h>
#include <shared/core/game_level.h>

void SH_Game::_ready()
{
    DISABLE_IN_EDITOR();
    ADD_RPC_CONFIG(movement_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(attack_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(ability_use_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
}

void SH_Game::_tick() {

}

GameLevel *SH_Game::load_game_level(const String& level_name)
{
    //Let others know that level is changing
    emit_signal("pre_level_load");
    Ref<PackedScene> game_level_scene = ResourceLoader::load("res://levels/" + level_name + ".tscn");
    GameLevel *game_level_tmp = Object::cast_to<GameLevel>(game_level_scene->instantiate());
    ERR_FAIL_NULL_V(game_level_tmp, nullptr);
    game_level_tmp->set_name("Level");
    game_level = game_level_tmp;
    add_child(game_level);
    //Let others know that level has changed
    emit_signal("post_level_load");
    return game_level;
}

void SH_Game::_init() {
    replication_config.instantiate();
    set_physics_process(true);
}

void SH_Game::add_node_networked_property(Node *node, const StringName &property_name)
{
    NodePath property_path = String(node->get_name()) + ":" + property_name;
    replication_config->add_property(property_path);
    replication_config->property_set_sync(property_path, false);
    replication_config->property_set_watch(property_path, true);
}

void SH_Game::remove_node_networked_property(Node *node, const StringName &property_name) {
    NodePath property_path = String(node->get_name()) + ":" + property_name;
    replication_config->remove_property(property_path);
}

void SH_Game::setup_game()
{

}

void SH_Game::_notification(int p_notification)
{
    DISABLE_IN_EDITOR();
    switch (p_notification)
    {
    case Node::NOTIFICATION_POSTINITIALIZE:
    {
        _init();
    }
    break;

    case Node::NOTIFICATION_READY:
    {
        print_line("Ready from sh_game.cpp");
        _ready();
    }
    break;

    case NOTIFICATION_PHYSICS_PROCESS:
    {
        //Process next game tick
        _tick();
    }
    break;

    default:
        break;
    }
}

void SH_Game::_bind_methods()
{

    ClassDB::bind_method(D_METHOD("movement_request", "target_position"), &SH_Game::movement_request);
    ClassDB::bind_method(D_METHOD("attack_request", "target_position"), &SH_Game::attack_request);
    ClassDB::bind_method(D_METHOD("ability_use_request", "target_position"), &SH_Game::ability_use_request);

    // Global game events
    ADD_SIGNAL(MethodInfo("on_basic_attack_hit", PropertyInfo(Variant::OBJECT, "target"), PropertyInfo(Variant::OBJECT, "inflictor"), PropertyInfo(Variant::OBJECT, "caused_by")));

    /*
    ClassDB::bind_method(D_METHOD("set_example_property", "value"), &SH_Game::set_example_property);
    ClassDB::bind_method(D_METHOD("get_example_property"), &SH_Game::get_example_property);
    ClassDB::bind_method(D_METHOD("set_example_grouped_property", "value"), &SH_Game::set_example_grouped_property);
    ClassDB::bind_method(D_METHOD("get_example_grouped_property"), &SH_Game::get_example_grouped_property);


    ADD_GROUP("Shared", "");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "example_grouped_property"), "set_example_grouped_property", "get_example_grouped_property");
    ADD_SUBGROUP("Example subgroup", "");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "example_property"), "set_example_property", "get_example_property");
    */
}

void SH_Game::send_game_info_to(int peer_id)
{
    //FIXME: Dictionaries may store callable, which can result in RCE vulnerability?
    /*
    Dictionary gameinfo;
    gameinfo["gamelevel"] = get_current_level()->get_scene_file_path();

    Dictionary players_info;
    for(auto kv : players_by_peerid)
    {
        Ref<Player> player = kv.value;
        Dictionary playerdata;
        playerdata["nickname"] = player->get_nickname();
        playerdata["mercenary"] = player->get_choosen_mercenary();
        players_info[kv.key] = playerdata;
    }

    gameinfo["players_info"] = players_info;

    rpc_id(peer_id, "parse_game_info", gameinfo);
    */
}

GameLevel *SH_Game::get_current_level()
{
    return game_level;
}

void SH_Game::movement_request(Vector2 target_pos) {
    movement_request_impl(target_pos);
}
void SH_Game::attack_request(Vector2 target_pos, uint64_t target_entity_id) {
    attack_request_impl(target_pos, target_entity_id);
}
void SH_Game::ability_use_request(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id) {
    ability_use_request_impl(ability_id, target_pos, target_entity_id);
}
