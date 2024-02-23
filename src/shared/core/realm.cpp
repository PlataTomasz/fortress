#include "realm.h"

#include <shared/helper_macros.h>
#include <scene/main/multiplayer_api.h>
#include <scene/main/multiplayer_peer.h>

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
    
    default:
        break;
    }
}

void Realm::_ready() {
    DISABLE_IN_EDITOR();
    ADD_RPC_CONFIG(server_rpc_disconnect, MultiplayerAPI::RPC_MODE_AUTHORITY, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(server_rpc_gameinfo, MultiplayerAPI::RPC_MODE_AUTHORITY, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(client_rpc_playerdata, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
}