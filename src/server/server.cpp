#include "server.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/scene/main/scene_tree.h>



void Server::_ready()
{
    this->networkPeer = memnew(ENetMultiplayerPeer);

    this->networkPeer->create_server(7654, 32, 4);

    Ref<MultiplayerAPI> mAPI = memnew(MultiplayerAPI);
    mAPI->set_multiplayer_peer(networkPeer);

    this->get_tree()->set_multiplayer(mAPI);
}