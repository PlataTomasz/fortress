#if !defined(COMMON_NODES_INCLUDED)
#define COMMON_NODES_INCLUDED

#include <scene/main/scene_tree.h>
#include <scene/main/window.h>
//TODO: Check with "ifdef" macro to avoid compilation errors
#include <server/server.h>

Server *get_game_server()
{
    return Server::get_instance();
}

#endif // COMMON_NODES_INCLUDED
