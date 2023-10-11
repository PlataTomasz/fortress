#if !defined(GAME_H_INCLUDED)
#define GAME_H_INCLUDED

#include <scene/3d/camera_3d.h>
#include <scene/main/node.h>
#include <scene/3d/node_3d.h>
#include <core/math/vector3.h>
#include <core/input/input_event.h>
#include "player.hpp"
#include "game_camera.hpp"

#include "map_loader.hpp"
#include "game_map.hpp"

class Client;
class C_SyncEvent;

/**
 * Performs game related logic such as input handling and managing smaller components.
 * Game is supposed to be added to scene once connection to server was established.
*/
class Game : public Node
{
GDCLASS(Game, Node);
private:

    List<C_SyncEvent *> sync_events;

    /**
     * Current map.
    */
    GameMap *gameMap = nullptr;
    GameCamera *camera = nullptr;
    Client *client = nullptr;

    void initialize_registries();
protected:
    void _notification(int notification);

public:
    Player *player;

    void ready();
    void unhandled_input(const Ref<InputEvent> &event) override;

    void put_sync_event(C_SyncEvent *sync_event);

    void onChildExitTree(Node* node)
    {
        //Detecting if GameMap was removed for some reason(why?)
        //TODO: Involve ObjectPtr class instead
        if(Object::cast_to<GameMap>(node))
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
