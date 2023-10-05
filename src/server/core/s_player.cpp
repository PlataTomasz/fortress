#include "s_player.h"

void S_Player::set_controlling_peer(ENetPeer *p_peer)
{
    if(peer != nullptr)
    {
        peer = p_peer;
    }
}