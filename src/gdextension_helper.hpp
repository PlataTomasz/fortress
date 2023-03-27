#if !defined(GDEXTENSION_HELPER_HPP_INCLUDED)
#define GDEXTENSION_HELPER_HPP_INCLUDED

#include <core/config/engine.h>
#include <scene/main/window.h>
#include <scene/main/node.h>
#include <scene/main/scene_tree.h>
#include <core/string/ustring.h>
#include <core/string/node_path.h>

#define DISABLE_IN_EDITOR() if(Engine::get_singleton()->is_editor_hint()) return;

class Client;
class Game;



static SceneTree* get_scene_tree()
{
    SceneTree* sceneTreeSingleton = (SceneTree*)SceneTree::get_singleton();
    return sceneTreeSingleton;
}

static Client* get_client()
{
    return (Client*)get_scene_tree()->get_root()->get_node(NodePath("Client"));
}

static Game* get_game()
{
    return (Game*)get_scene_tree()->get_root()->get_node(NodePath("Client/Game"));
}
#endif // GDEXTENSION_HELPER_HPP_INCLUDED
