#if !defined(GAME_H_INCLUDED)
#define GAME_H_INCLUDED

#include <scene/3d/camera_3d.h>
#include <scene/main/node.h>
#include <scene/3d/node_3d.h>
#include <core/math/vector3.h>

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
    virtual void unhandled_input(const Ref<InputEvent> &event) override;

    //Utilis
    Vector3 screenToWorld(const Vector2 &screenPos);
protected:
    static void _bind_methods();
public:
    Game();
    ~Game();
};

#endif // GAME_H_INCLUDED
