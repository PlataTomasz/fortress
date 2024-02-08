#include "player.h"
/*
void Player::set_controlling_peer(Ref<ENetPacketPeer> p_peer)
{
    if(peer.is_valid())
    {
        peer = p_peer;
    }
}

Ref<ENetPacketPeer> Player::get_controlling_peer()
{
    return peer;
}
*/
void Player::set_controlled_entity(Entity *p_controlled_entity)
{
    controlled_entity = p_controlled_entity;
}

Entity *Player::get_controlled_entity()
{
    return controlled_entity;
}

void Player::change_nickname(String p_nickname)
{
    nickname = p_nickname;
}

String Player::get_nickname()
{
    return nickname;
}