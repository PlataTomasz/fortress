#include "game.h"
#include <server/server.h>
#include <shared/helper_macros.h>
#include <shared/entities/living_entity.h>
#include <core/io/json.h>
#include <scene/scene_string_names.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <scene/resources/packed_scene.h>

#ifdef DEBUG_ARTSKR
#include <scene/3d/camera_3d.h>
#include <scene/main/viewport.h>
#include <shared/data_holders/use_context.hpp>
#endif


#include <scene/main/timer.h>
#include <shared/entities/components/movement/movement_component.h>

Game::Game()
{
    //Temporary
    gameinfo["level"] = "ExampleGameLevel";
}

void Game::_ready()
{
    DISABLE_IN_EDITOR();
    //No error checking!
    load_game_level(String(gameinfo["level"]));
    setup_game();
}

//Notifications are called cascade
void Game::_notification(int notification)
{
    DISABLE_IN_EDITOR();
    switch (notification)
    {
    case NOTIFICATION_READY:
    {
        _ready();
    }
    break;

    default:
        break;
    }
}

void Game::_bind_methods()
{

}

// Player send invalid playerdata or didn't send it at all - kick him
void Game::_on_playerdata_fail(int peer_id) {
    // Cleanup disconnect timer - no longer needed
    if (playerdata_timers.has(peer_id)) {
        Ref<SceneTreeTimer> timer = playerdata_timers.get(peer_id);
    }

    print_line("Peer ", peer_id, " disconnected. Reason: Invalid playerdata");
    server->disconnect_peer(peer_id, "Invalid playerdata!");
}

// Expected to arrive shortly after player connects
void Game::_on_receive_playerdata(Dictionary playerdata) {
    int peer_id = get_multiplayer()->get_remote_sender_id();
    Ref<Player> ply = server->get_player(peer_id);

}

void Game::attack_request_impl(Vector2 target_pos, uint64_t target_entity_id) {
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Attack request received from", peer_id);
}

void Game::ability_use_request_impl(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id) {
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Ability use request received from", peer_id);
}

void Game::player_cfg_update_request_impl(Dictionary player_cfg) {
    ERR_FAIL_COND(player_cfg.has("nickname" ));
    ERR_FAIL_COND(player_cfg.has("mercenary"));

    //_on_player_connect(get_multiplayer()->get_remote_sender_id(), player_cfg.get("nickname", "unexpected"));
}

void Game::movement_request_impl(Vector2 target_pos)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();

    print_line("Movement request to", target_pos, "from peer", peer_id);
    
    Ref<Player> player = server->get_player(peer_id);
    ERR_FAIL_COND_MSG(player.is_null(), "Sender peer has no corresponding player");

    Entity *issuer = player->get_controlled_entity();
    ERR_FAIL_COND_MSG(!issuer, "Player doesn't controll any entity!");

    LivingEntity *movement_target = Object::cast_to<LivingEntity>(player->get_controlled_entity());
    ERR_FAIL_COND_MSG(!movement_target, "Entity cannot take movement requests!");

    MovementComponent *movement_component = static_cast<MovementComponent *>(issuer->get_component("MovementComponent"));
    ERR_FAIL_NULL(movement_component);
    movement_component->set_destination_position(Vector3(target_pos.x,0,target_pos.y));

    //TODO: Parse movement request here

    //FIXME: Connection is established, RPC work, Replication doesn't
    //Entity *ent = static_cast<Entity *>(get_node(NodePath("Level/Entities/Entity")));

    //ent->set_position(ent->get_position() + Vector3(1,0,0));
}