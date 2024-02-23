#if !defined(SERVER_GAME_INCLUDED)
#define SERVER_GAME_INCLUDED

//For some reason "#include <scene/main/node.h>" directly, fails - This is workaround
#include <scene/main/canvas_item.h>
#include <shared/core/game_level.h>
#include <shared/helpers/object_ptr.h>
#include <modules/multiplayer/scene_replication_config.h>

#include <shared/core/player.h>
#include <shared/core/sh_game.h>

class Server;

class Game : public SH_Game
{
GDCLASS(Game, SH_Game);
private:
    Server *server = nullptr;

    // Seems messy - Reimplment one day
    HashMap<int, Ref<SceneTreeTimer>> playerdata_timers;

    Dictionary gameinfo;

    void _on_peer_connect(int peer_id);
    void _on_peer_disconnect(int peer_id);

    void _ready();

    void _on_receive_playerdata(Dictionary playerdata);
protected:
    void _notification(int notification);

    static void _bind_methods();
public:
    void disconnect_peer(int peer_id, const char *reason = "Disconnected");

    void _on_playerdata_fail(int peer_id);

    //Request handling methods
    virtual void player_cfg_update_request_impl(Dictionary player_cfg);
    virtual void movement_request_impl(Vector2 target_pos);
    virtual void attack_request_impl(Vector2 target_pos, uint64_t target_entity_id);
    virtual void ability_use_request_impl(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id);
    Game();

    friend class Server;
};

#endif // SERVER_GAME_INCLUDED
