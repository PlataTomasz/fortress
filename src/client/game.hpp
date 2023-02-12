#if !defined(GAME_H_INCLUDED)
#define GAME_H_INCLUDED

#include <classes/camera3d.hpp>
#include <classes/node.hpp>
#include <classes/node3d.hpp>
#include <variant/vector3.hpp>
#include <classes/input_event.hpp>
#include "player.hpp"
#include "game_camera.hpp"

#include "map_loader.hpp"
#include "game_map.hpp"

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
    GameMap *gameMap = nullptr;
    GameCamera *camera = nullptr;
public:
    Player *player;

    void _ready() override;
    void _unhandled_input(const Ref<InputEvent> &event) override;

    void onChildExitTree(Node* node)
    {
        //Detecting if GameMap was removed for some reason(why?)
        if(GameMap* ent = Object::cast_to<GameMap>(node))
        {
            gameMap = nullptr;
        }

        //Otherwise do nothing
    }

    void onChildEnterTree(Node* node)
    {
        //Auto detect map change
    }

    GameMap* getGameMap()
    {
        return this->gameMap;
    }

    //Utilis
    Vector3 screenToWorld(const Vector2 &screenPos);
protected:
    static void _bind_methods();
public:
    Game();
    ~Game();
};

#endif // GAME_H_INCLUDED
