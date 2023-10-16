#if !defined(S_COMMON_NODES_INCLUDED)
#define S_COMMON_NODES_INCLUDED

#include <scene/main/scene_tree.h>
#include <scene/main/window.h>
#include <server/server.h>

Server *get_game_server()
{
    SceneTree* sceneTreeSingleton = (SceneTree*)SceneTree::get_singleton();
    return reinterpret_cast<Server *>(sceneTreeSingleton->get_root()->get_node(NodePath("Server")));
}

#endif // S_COMMON_NODES_INCLUDED
