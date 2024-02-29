#include "realm.h"

#include <shared/helper_macros.h>
#include <scene/main/multiplayer_api.h>
#include <scene/main/multiplayer_peer.h>
#include <modules/multiplayer/multiplayer_synchronizer.h>
#include <modules/multiplayer/multiplayer_spawner.h>

Game *Realm::game = nullptr;

Game *Realm::get_game()
{
    return game;
}

void Realm::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
    switch (p_notification)
    {
    case NOTIFICATION_READY:
        _ready();
        break;
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        break;
    default:
        break;
    }
}

void Realm::_init() {
    replication_config.instantiate();
}

void Realm::_ready() {
    DISABLE_IN_EDITOR();
    ADD_RPC_CONFIG(server_rpc_disconnect, MultiplayerAPI::RPC_MODE_AUTHORITY, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(server_rpc_gameinfo, MultiplayerAPI::RPC_MODE_AUTHORITY, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(client_rpc_playerdata, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(server_rpc_set_controlled_entity, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);

    realm_data_synchronizer = memnew(MultiplayerSynchronizer);
	realm_data_synchronizer->set_name("RealmDataSynchronizer");
	add_child(realm_data_synchronizer);

    realm_data_synchronizer->set_root_path(get_path());
    realm_data_synchronizer->set_replication_config(replication_config);

    MultiplayerSpawner *player_spawner = nullptr;
    player_spawner = memnew(MultiplayerSpawner);
    player_spawner->set_name("PlayerSpawner");
    
    player_spawner->set_spawn_path(NodePath("../Players"));

    //player_spawner->spawn();
}

Node *Realm::_player_spawner(Variant &data) {
    Dictionary data_dict;
    if (data.get_type() == Variant::DICTIONARY) {
        Variant var_peer_id = data_dict.get_valid("nickname");
        Variant var_nickname = data_dict.get_valid("peer_id");

        
    }

    return nullptr;
}