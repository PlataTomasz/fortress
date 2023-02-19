#if !defined(GDEXTENSION_HELPER_HPP_INCLUDED)
#define GDEXTENSION_HELPER_HPP_INCLUDED

#include <classes/scene_tree.hpp>
#include <classes/engine.hpp>

#define DISABLE_IN_EDITOR() if(Engine::get_singleton()->is_editor_hint()) return;

class Client;
class Game;

static Client* get_client()
{
    return get_scene_tree()->get_root()->get_node<Client>("Client");
}

static Game* get_game()
{
    return get_scene_tree()->get_root()->get_node<Game>("Client/Game");
}


static SceneTree* get_scene_tree()
{
    SceneTree* sceneTreeSingleton = (SceneTree*)Engine::get_singleton()->get_main_loop();
    return sceneTreeSingleton;
}

#endif // GDEXTENSION_HELPER_HPP_INCLUDED
