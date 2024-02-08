#if !defined(COMMON_NODES_INCLUDED)
#define COMMON_NODES_INCLUDED

#include <scene/main/scene_tree.h>
#include <scene/main/window.h>
//TODO: Check with "ifdef" macro to avoid compilation errors
#include <server/server.h>

Server *get_game_server()
{
    SceneTree* sceneTreeSingleton = (SceneTree*)SceneTree::get_singleton();
    return reinterpret_cast<Server *>(sceneTreeSingleton->get_root()->get_node(NodePath("Server")));
}

#endif // COMMON_NODES_INCLUDED
