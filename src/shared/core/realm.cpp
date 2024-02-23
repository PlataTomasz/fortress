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
    ADD_RPC_CONFIG(disconnected_by_server, MultiplayerAPI::RPC_MODE_AUTHORITY, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
}