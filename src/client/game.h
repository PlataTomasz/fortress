#if !defined(GAME_H_INCLUDED)
#define GAME_H_INCLUDED

#include <scene/3d/camera_3d.h>
#include <scene/main/node.h>
#include <scene/3d/node_3d.h>
#include <core/math/vector3.h>
#include <core/input/input_event.h>

#include <shared/core/player.h>
#include "game_camera.hpp"
#include <shared/core/game_level.h>
#include <shared/core/sh_game.h>

class Client;

/**
 * Performs game related logic such as input handling and managing smaller components.
 * Game is supposed to be added to scene once connection to server was established.
*/
class Game : public SH_Game
{
GDCLASS(Game, SH_Game);
private:
    GameCamera *game_camera = nullptr;
    Client *client = nullptr;

    //void _on_entity_remote_spawn(Node *p_node);


    //Called when all steps of connection to server are completed and server gave us gameinfo
public:
    void fetch_mercenary_classes(List<StringName> &names) {
        ClassDB::get_inheriters_from_class("Mercenary", &names);
    };

    void _init();
    void _ready();
    void _tick();
    void unhandled_input(const Ref<InputEvent> &event) override;

    //Request RPC methods - Empty, exist only to match RPC signature on authority, to avoid checksum errors
    virtual void movement_request_impl(Vector2 target_pos);
    virtual void attack_request_impl(Vector2 target_pos, uint64_t target_entity_id);
    virtual void ability_use_request_impl(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id);

    GameCamera *setup_game_camera();

    //Utilis
    Vector3 screenToWorld(const Vector2 &screenPos);
protected:
    static void _bind_methods();

    void _notification(int p_notification);
public:
    Game();
    ~Game();
};

#endif // GAME_H_INCLUDED
