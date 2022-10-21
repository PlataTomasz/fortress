#include "client.h"
#include <iostream>

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

void Client::_enter_tree()
{
    this->add_child(ui);

}

void Client::_ready()
{
    //Initialize network Peer
    multiplayerPeer = memnew(ENetMultiplayerPeer);
    multiplayerPeer->create_client("localhost", 7654, 4);

    Ref<MultiplayerAPI> mAPI = memnew(MultiplayerAPI);

    this->get_tree()->set_multiplayer(mAPI);
}

void Client::_process()
{

}

void Client::_bind_methods()
{
    //ClassDB::bind_method(D_METHOD("_process"), &Client::_process);
    /*
    ClassDB::bind_method(D_METHOD("get_class"), &Client::get_class);
    ClassDB::bind_method(D_METHOD("_ready"), &Client::_ready);
    ClassDB::bind_method(D_METHOD("_enter_tree"), &Client::_enter_tree);
    */
}