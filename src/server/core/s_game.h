#if !defined(SERVER_GAME_INCLUDED)
#define SERVER_GAME_INCLUDED

//For some reason "#include <scene/main/node.h>" directly, fails - This is workaround
#include <scene/main/canvas_item.h>
#include <server/core/game_commands/s_game_commands.h>
#include "s_game_level.h"

#include "s_player.h"

class Server;

class S_Game : public Node
{
GDCLASS(S_Game, Node);
private:
    Server *server;
    
    HashMap<int, Ref<S_Player>> players_by_peerid;

    //Currently hardcoded at 10 players - unused ones are just inactive
    List<Ref<S_Player>> players;

    //Game commands to be executed in the next frame
    List<S_GameCommand *> game_commands;

    HashMap<uint64_t, S_BaseEntity *> networked_entities;

    void _on_player_connect(int peer_id, String nickname);
    void _on_player_disconnect(int peer_id);

    void fixed_tick();

    void _ready();

    void setup_game();

    MultiplayerSynchronizer *entity_synchronizer = nullptr;
    MultiplayerSpawner *entity_spawner = nullptr;
protected:
    void _notification(int notification);

    static void _bind_methods();
public:
    Ref<S_Player> get_player_by_peerid(int peerid);
    void add_player(Ref<S_Player> player){players.push_back(player);};

    //Request handling methods
    void player_cfg_update_request(Dictionary player_cfg);

    void movement_request(Vector2 target_pos);
    void attack_request(Vector2 target_pos, uint64_t target_entity_id);
    void ability_use_request(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id);

    

    //Other networking methods
    void send_game_info_to(int peer_id);

    void put_game_command(S_GameCommand *gamecmd);
    
    /**
     * @return Pointer to current map or nullptr if map is not set
    */
    S_GameLevel *get_current_level();
    S_Game();
};

#endif // SERVER_GAME_INCLUDED
