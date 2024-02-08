#include "game.h"
#include <server/server.h>
#include <shared/helper_macros.h>
#include <shared/entities/living_entity.h>
#include <core/io/json.h>
#include <scene/scene_string_names.h>
#include <shared/entities/mercenaries/mercenary.hpp>

#ifdef DEBUG_ARTSKR
#include <scene/3d/camera_3d.h>
#include <scene/main/viewport.h>
#include <shared/data_holders/use_context.hpp>
#endif

Game::Game()
{
    DISABLE_IN_EDITOR();
    set_physics_process(true);

    ADD_RPC_CONFIG(movement_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(attack_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(ability_use_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(player_cfg_update_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    
    Player *p1 = memnew(Player);
    p1->change_nickname("Boris");
    add_player(p1);

    Player *p2 = memnew(Player);
    p1->change_nickname("Jar'ro");
    add_player(p2);
}

void Game::add_node_networked_property(ObjectPtr<Node> node, StringName property_name)
{
    NodePath property_path = String(node->get_path()) + ":" + property_name;
    replication_config->add_property(property_path);
    replication_config->property_set_sync(property_path, false);
    replication_config->property_set_watch(property_path, true);
}

void Game::setup_game()
{
    mp_synchronizer = memnew(MultiplayerSynchronizer);
    mp_spawner = memnew(MultiplayerSpawner);

    add_child(mp_synchronizer.get_ptr());
    add_child(mp_spawner.get_ptr());

    NodePath entities_nodepath = NodePath("../Level/Entities");

    mp_spawner->set_spawn_path(entities_nodepath);
    mp_spawner->add_spawnable_scene("res://entities/Entity.tscn");

    mp_synchronizer->set_root_path(entities_nodepath);

    if(mp_synchronizer->get_replication_config().is_null())
        mp_synchronizer->set_replication_config(memnew(SceneReplicationConfig));

}

void Game::_ready()
{
    //
}

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

    case NOTIFICATION_PHYSICS_PROCESS:
    {
        //Process next game tick
        fixed_tick();
    }
    break;

    case NOTIFICATION_ENTER_TREE:
    {
        server = static_cast<Server *>(get_parent());
    }
    break;
    
    default:
        break;
    }
}

void Game::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("movement_request", "target_position"), &Game::movement_request);
    ClassDB::bind_method(D_METHOD("attack_request", "target_position"), &Game::attack_request);
    ClassDB::bind_method(D_METHOD("ability_use_request", "target_position"), &Game::ability_use_request);
    ClassDB::bind_method(D_METHOD("player_cfg_update_request", "player_cfg"), &Game::player_cfg_update_request);
}

void Game::send_game_info_to(int peer_id)
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

void Game::movement_request(Vector2 target_pos)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();

    print_line("Movement request to", target_pos, "from", peer_id);

    Ref<Player> player = get_player_by_peerid(peer_id);
    ERR_FAIL_COND_MSG(player.is_null(), "Sender peer has no corresponding player");

    Entity *issuer = player->get_controlled_entity();
    ERR_FAIL_COND_MSG(!issuer, "Player doesn't controll any entity!");

    LivingEntity *movement_target = Object::cast_to<LivingEntity>(player->get_controlled_entity());
    ERR_FAIL_COND_MSG(!movement_target, "Entity cannot take movement requests!");

    //TODO: Parse movement request here
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

void Game::player_cfg_update_request(Dictionary player_cfg)
{
    ERR_FAIL_COND(player_cfg.has("nickname"));
    ERR_FAIL_COND(player_cfg.has("mercenary"));

    _on_player_connect(get_multiplayer()->get_remote_sender_id(), player_cfg.get("nickname", "unexpected"));
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

GameLevel *Game::get_current_level()
{
    return Object::cast_to<GameLevel>(get_node_or_null(NodePath("Level")));
}

void Game::attack_request(Vector2 target_pos, uint64_t entity_id)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Attack request received from", peer_id);
}

void Game::ability_use_request(uint8_t ability_id, Vector2 target_pos, uint64_t entity_id)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Ability use request received from", peer_id);
}

#ifdef DEBUG_ARTSKR
Vector3 Game::screenToWorld(const Vector2 &screenPos)
{
    Camera3D *camera = Object::cast_to<Camera3D>(get_node(NodePath("Camera3D")));
    ERR_FAIL_COND_V(!camera, Vector3(0,0,0));
    //TODO: Project need to be used on camera node

    Vector3 roughWorldPos = camera->project_position(screenPos, 1000);
    Vector3 clickPos = camera->project_ray_origin(screenPos);

    double l = (roughWorldPos.x - clickPos.x);
    double m = (roughWorldPos.y - clickPos.y);
    double n = (roughWorldPos.z - clickPos.z);

    double world_x = clickPos.x - (clickPos.y/m)*l;
    double world_z = clickPos.z - (clickPos.y/m)*n;

    //y is zero because that doesn't matter
    return Vector3(world_x, 0, world_z);
}

void Game::unhandled_input(const Ref<InputEvent> &event)
{
    //Casting to InputEventMouseButton - If succeeds: It is valid type
    if(InputEventMouseButton *input_event_mouse_btn = Object::cast_to<InputEventMouseButton>(event.ptr()))
    {
        Vector2 screenPos = input_event_mouse_btn->get_position();
        Vector3 worldPos = screenToWorld(screenPos);

        UseContext use_context = {
            players[0]->get_controlled_entity(),
            players[0]->get_controlled_entity()->get_position(),
            Vector<Vector3>({worldPos}),
            Vector<Entity*>()
        };

        //Convert screen to world cordinates
        printf("{ %f, %f, %f}\n", worldPos.x, worldPos.y, worldPos.z);

        if(input_event_mouse_btn->is_action_pressed("basic_attack"))
        {
            print_line("ATTACK_ACTION");

            //player->controlledEntity->use_basic_attack(use_context);

            Error err = rpc("attack_request", Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_mouse_btn->is_action_pressed("movement"))
        {
            print_line("MOVEMENT_ACTION");
            
            Error err = rpc("movement_request", Vector2(worldPos.x, worldPos.z));
            print_line("Client RPC Error", err);
        }
    }
    else if(const InputEventKey *input_event_key = Object::cast_to<InputEventKey>(event.ptr()))
    {
        Vector3 worldPos = screenToWorld(get_viewport()->get_mouse_position());

        UseContext use_context = {
            players[0]->get_controlled_entity(),
            players[0]->get_controlled_entity()->get_position(),
            Vector<Vector3>({worldPos}),
            Vector<Entity*>()
        };

        //TODO: Ability use indicators
        if(input_event_key->is_action_pressed("cast_ability_1"))
        {
            printf("Q press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_FIRST, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_FIRST, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_2"))
        {
            printf("W press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_SECOND, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_SECOND, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_3"))
        {
            printf("E press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_THIRD, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_THIRD, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_4"))
        {
            printf("R press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_ULTIMATE, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_ULTIMATE, Vector2(worldPos.x, worldPos.z), 0);
        }
    }
}
#endif