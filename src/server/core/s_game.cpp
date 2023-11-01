#include "s_game.h"
#include <server/server.h>
#include <shared/helper_macros.h>
#include <server/entities/s_living_entity.h>
#include <core/io/json.h>
#include <scene/scene_string_names.h>

S_Game::S_Game()
{
    DISABLE_IN_EDITOR();
    set_physics_process(true);

    ADD_RPC_CONFIG(movement_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(attack_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(ability_use_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    

}

void S_Game::setup_game()
{
    entity_synchronizer = memnew(MultiplayerSynchronizer);
    entity_spawner = memnew(MultiplayerSpawner);

    add_child(entity_spawner);
    add_child(entity_synchronizer);

    NodePath entities_nodepath = NodePath("../Level/Entities");

    entity_spawner->set_spawn_path(entities_nodepath);
    entity_spawner->add_spawnable_scene("res://entities/Entity.tscn");

    entity_synchronizer->set_root_path(entities_nodepath);

    if(entity_synchronizer->get_replication_config().is_null())
        entity_synchronizer->set_replication_config(memnew(SceneReplicationConfig));

}

void S_Game::_ready()
{
    get_multiplayer()->connect(SNAME("peer_connected"), callable_mp(this, &S_Game::send_game_info_to));
    setup_game();
}

void S_Game::_notification(int notification)
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

void S_Game::fixed_tick()
{
    //Dispatch game commands
    for(auto cmd : game_commands)
    {
        cmd->execute(this);
        delete cmd;
    }

    game_commands.clear();
}

void S_Game::put_game_command(S_GameCommand *gamecmd)
{
    game_commands.push_back(gamecmd);
}

void S_Game::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("movement_request", "target_position"), &S_Game::movement_request);
    ClassDB::bind_method(D_METHOD("attack_request", "target_position"), &S_Game::attack_request);
    ClassDB::bind_method(D_METHOD("ability_use_request", "target_position"), &S_Game::ability_use_request);
}

void S_Game::send_game_info_to(int peer_id)
{
    //FIXME: Dictionaries may store callable, which can result in RCE vulnerability?
    Dictionary gameinfo;
    gameinfo["gamelevel"] = get_current_level()->get_scene_file_path();

    Dictionary players_info;
    for(auto kv : players_by_peerid)
    {
        Ref<S_Player> player = kv.value;
        Dictionary playerdata;
        playerdata["nickname"] = player->get_nickname();
        playerdata["mercenary"] = player->get_choosen_mercenary();
        players_info[kv.key] = playerdata;
    }

    gameinfo["players_info"] = players_info;

    rpc_id(peer_id, "parse_game_info", gameinfo);
}

void S_Game::movement_request(Vector2 target_pos)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();

    print_line("Movement request to", target_pos, "from", peer_id);

    Ref<S_Player> player = get_player_by_peerid(peer_id);
    ERR_FAIL_COND_MSG(player.is_null(), "Sender peer has corresponding player");

    S_BaseEntity *issuer = player->get_controlled_entity();
    ERR_FAIL_COND_MSG(!issuer, "Player doesn't controll any entity!");

    S_LivingEntity *movement_target = Object::cast_to<S_LivingEntity>(player->get_controlled_entity());
    ERR_FAIL_COND_MSG(!movement_target, "Entity cannot take movement requests!");

    S_GameCommandMovement *gamecmd_movement = new S_GameCommandMovement(issuer, movement_target, target_pos);
}

Ref<S_Player> S_Game::get_player_by_peerid(int peerid)
{
    if(players_by_peerid.has(peerid))
        return players_by_peerid.get(peerid);
    else
        return Ref<S_Player>();
}

void S_Game::attack_request(Vector2 target_pos, uint64_t entity_id)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Attack request received from", peer_id);
}

void S_Game::ability_use_request(uint8_t ability_id, Vector2 target_pos, uint64_t entity_id)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Ability use request received from", peer_id);
}