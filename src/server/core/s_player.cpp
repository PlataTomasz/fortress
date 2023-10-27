#include "s_player.h"
/*
void S_Player::set_controlling_peer(Ref<ENetPacketPeer> p_peer)
{
    if(peer.is_valid())
    {
        peer = p_peer;
    }
}

Ref<ENetPacketPeer> S_Player::get_controlling_peer()
{
    return peer;
}
*/
void S_Player::set_controlled_entity(S_BaseEntity *p_controlled_entity)
{
    controlled_entity = p_controlled_entity;
}

S_BaseEntity *S_Player::get_controlled_entity()
{
    return controlled_entity;
}

void S_Player::change_nickname(String p_nickname)
{
    nickname = p_nickname;
}

String S_Player::get_nickname()
{
    return nickname;
}