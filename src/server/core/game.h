#if !defined(SERVER_GAME_INCLUDED)
#define SERVER_GAME_INCLUDED

//For some reason "#include <scene/main/node.h>" directly, fails - This is workaround
#include <scene/main/canvas_item.h>
#include <shared/core/game_level.h>
#include <shared/helpers/object_ptr.h>

#include <shared/core/player.h>

class Server;

class Game : public Node
{
GDCLASS(Game, Node);
private:
    ObjectPtr<MultiplayerSynchronizer> mp_synchronizer;
    ObjectPtr<MultiplayerSpawner> mp_spawner;

    Ref<SceneReplicationConfig> replication_config;

    Server *server;
    
    HashMap<int, Ref<Player>> players_by_peerid;

    //Currently hardcoded at 10 players - unused ones are just inactive
    List<Ref<Player>> players;

    void _on_player_connect(int peer_id, String nickname);
    void _on_player_disconnect(int peer_id);

    void fixed_tick();

    void _ready();

    void setup_game();
protected:
    void _notification(int notification);

    static void _bind_methods();
public:
    #ifdef DEBUG_ARTSKR
    Vector3 screenToWorld(const Vector2 &screenPos);
    void unhandled_input(const Ref<InputEvent> &event) override;
    #endif

    //Network synchronization stuff
    void add_node_networked_property(ObjectPtr<Node> node, StringName property_name);

    Ref<Player> get_player_by_peerid(int peerid);
    void add_player(Ref<Player> player){players.push_back(player);};

    //Request handling methods
    void player_cfg_update_request(Dictionary player_cfg);

    void movement_request(Vector2 target_pos);
    void attack_request(Vector2 target_pos, uint64_t target_entity_id);
    void ability_use_request(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id);

    //Other networking methods
    void send_game_info_to(int peer_id);
    
    /**
     * @return Pointer to current map or nullptr if map is not set
    */
    GameLevel *get_current_level();
    Game();
};

#endif // SERVER_GAME_INCLUDED
