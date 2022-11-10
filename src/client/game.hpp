#if !defined(GAME_H_INCLUDED)
#define GAME_H_INCLUDED

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>

#include "map_loader.hpp"

using namespace godot;
/**
 * Performs game related logic such as input handling and managing smaller components.
 * Game is supposed to be added to scene once connection to server was established.
*/
class Game : public Node
{
GDCLASS(Game, Node);
private:
    /**
     * Current map.
    */
    Node3D *mapInstance = nullptr;
    Camera3D *camera = nullptr;
public:

    virtual void _ready();
    virtual void _unhandled_input(const Ref<InputEvent> &event);

    //Utilis
    Vector3 screenToWorld(const Vector2 &screenPos);
protected:
    static void _bind_methods();
public:
    Game();
    ~Game();
};

#endif // GAME_H_INCLUDED
