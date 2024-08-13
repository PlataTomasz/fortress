#include "player.h"

#include <shared/entities/entity.h>
#include <shared/entities/mercenaries/mercenary.hpp>

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
void Player::set_controlled_entity(Mercenary *p_controlled_entity)
{
    ERR_FAIL_NULL(p_controlled_entity);
    Mercenary *old = controlled_entity;
    controlled_entity = p_controlled_entity;
    controlled_entity->set_displayed_name(get_nickname());

    emit_signal("on_controlled_entity_changed", controlled_entity);
    // Notify entity that player which controlls it changed
    
}

void Player::cleanup_after_disconnect() {
    controlled_entity = nullptr;
}

Mercenary *Player::get_controlled_entity()
{
    return controlled_entity;
}

void Player::change_nickname(const String p_nickname)
{
    nickname = p_nickname;
}

String Player::get_nickname()
{
    return nickname;
}

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_nickname"), &Player::get_nickname);
    ClassDB::bind_method(D_METHOD("set_nickname", "nickname"), &Player::change_nickname);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "nickname"), "set_nickname", "get_nickname");

    ClassDB::bind_method(D_METHOD("get_choosen_mercenary"), &Player::get_choosen_mercenary);
    ClassDB::bind_method(D_METHOD("set_choosen_mercenary", "mercenary_name"), &Player::set_choosen_mercenary);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "mercenary_name"), "set_choosen_mercenary", "get_choosen_mercenary");

    ADD_SIGNAL(MethodInfo("on_controlled_entity_changed", PropertyInfo(Variant::OBJECT, "old_entity"), PropertyInfo(Variant::OBJECT, "new_entity")));
}