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

Game::Game()
{

}

void Game::_ready()
{
    DISABLE_IN_EDITOR();
    Player *p1 = memnew(Player);
    p1->change_nickname("Boris");
    add_player(p1);

    Player *p2 = memnew(Player);
    p1->change_nickname("Jar'ro");
    add_player(p2);
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

Ref<Player> Game::get_player_by_peerid(int peerid)
{
    for(Ref<Player> player : players)
    {
        if(player->get_owner_peer_id() == peerid)
        {
            return player;
        }
    }
    return Ref<Player>();
}

void Game::_on_player_connect(int peer_id, String nickname)
{
    print_line("player nickname:", nickname, "peer", peer_id);

    for( Ref<Player> player : players)
    {
        if(player->get_nickname() == nickname)
        {
            ERR_FAIL_COND_MSG(player->get_owner_peer_id() != 0, "Attempted to take control over player, which is already controlled!");
            player->set_owner_peer_id(peer_id);
        }
        else
        {
            ERR_FAIL_MSG("No such player precreated on server!");
        }
    }
}

void Game::_on_player_disconnect(int peer_id)
{
    for( Ref<Player> player : players)
    {
        if(player->get_owner_peer_id() == peer_id)
        {
            //Open for new peer to take control over that player
            player->set_owner_peer_id(0);
        }
    }
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

    _on_player_connect(get_multiplayer()->get_remote_sender_id(), player_cfg.get("nickname", "unexpected"));
}

void Game::movement_request_impl(Vector2 target_pos)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();

    print_line("Movement request to", target_pos, "from", peer_id);
    

    Ref<PackedScene> ent_scene = ResourceLoader::load("res://resources/entities/Entity.tscn");

    Entity *ent = static_cast<Entity *>(ent_scene->instantiate());
    ent->set_position(Vector3(21,3,7));
    ent->set_name(itos(ent->get_instance_id()));
    Node *level_entities = game_level->get_node(NodePath("Entities"));
    level_entities->add_child(ent);
    
    Ref<Player> player = get_player_by_peerid(peer_id);
    ERR_FAIL_COND_MSG(player.is_null(), "Sender peer has no corresponding player");

    Entity *issuer = player->get_controlled_entity();
    ERR_FAIL_COND_MSG(!issuer, "Player doesn't controll any entity!");

    LivingEntity *movement_target = Object::cast_to<LivingEntity>(player->get_controlled_entity());
    ERR_FAIL_COND_MSG(!movement_target, "Entity cannot take movement requests!");

    //TODO: Parse movement request here

    //FIXME: Connection is established, RPC work, Replication doesn't
    //Entity *ent = static_cast<Entity *>(get_node(NodePath("Level/Entities/Entity")));

    //ent->set_position(ent->get_position() + Vector3(1,0,0));
}