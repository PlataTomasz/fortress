#if !defined(GDEXTENSION_HELPER_HPP_INCLUDED)
#define GDEXTENSION_HELPER_HPP_INCLUDED

#include <classes/engine.hpp>
#include <classes/window.hpp>
#include <classes/node.hpp>
#include <classes/scene_tree.hpp>

#define DISABLE_IN_EDITOR() if(Engine::get_singleton()->is_editor_hint()) return;

class Client;
class Game;

using namespace godot;

static SceneTree* get_scene_tree()
{
    SceneTree* sceneTreeSingleton = (SceneTree*)Engine::get_singleton()->get_main_loop();
    return sceneTreeSingleton;
}

static Client* get_client()
{
    return (Client*)get_scene_tree()->get_root()->get_node<Node>("Client");
}

static Game* get_game()
{
    return (Game*)get_scene_tree()->get_root()->get_node<Node>("Client/Game");
}
#endif // GDEXTENSION_HELPER_HPP_INCLUDED
