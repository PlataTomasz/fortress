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
    
    HashMap<int, Ref<Player>> players_by_peerid;

    //Currently hardcoded at 10 players - unused ones are just inactive
    List<Ref<Player>> players;

    void _on_player_connect(int peer_id, String nickname);
    void _on_player_disconnect(int peer_id);

    void _ready();
protected:
    void _notification(int notification);

    static void _bind_methods();
public:
    Ref<Player> get_player_by_peerid(int peerid);
    void add_player(Ref<Player> player){players.push_back(player);};

    //Request handling methods
    virtual void player_cfg_update_request_impl(Dictionary player_cfg);
    virtual void movement_request_impl(Vector2 target_pos);
    virtual void attack_request_impl(Vector2 target_pos, uint64_t target_entity_id);
    virtual void ability_use_request_impl(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id);
    Game();
};

#endif // SERVER_GAME_INCLUDED
