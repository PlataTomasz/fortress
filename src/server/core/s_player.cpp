#include "s_player.h"

void SPlayer::set_controlling_peer(ENetPeer *p_peer)
{
    if(peer != nullptr)
    {
        peer = p_peer;
    }
}