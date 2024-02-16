#if !defined(SH_GAME_INCLUDED)
#define SH_GAME_INCLUDED

#include <modules/multiplayer/scene_replication_config.h>
#include <scene/main/node.h>

class GameLevel;
class MultiplayerSynchronizer;
class MultiplayerSpawner;

//NOTE: Should be abstract(in term of engine)
class SH_Game : public Node {
GDCLASS(SH_Game, Node);
private:
protected:
    MultiplayerSynchronizer *mp_synchronizer = nullptr;
    MultiplayerSpawner *mp_spawner = nullptr;

    Ref<SceneReplicationConfig> replication_config;

    GameLevel *game_level = nullptr;

    void _init();
    void _ready();
    void _tick();

    void setup_game();
    void _notification(int p_notification);

    static void _bind_methods();
public:
    //Network synchronization stuff
    void add_node_networked_property(Node *node, const StringName &property_name);

    //Request handling methods
    void player_cfg_update_request(Dictionary player_cfg);
    void movement_request(Vector2 target_pos);
    void attack_request(Vector2 target_pos, uint64_t target_entity_id);
    void ability_use_request(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id);

    virtual void player_cfg_update_request_impl(Dictionary player_cfg) = 0;
    virtual void movement_request_impl(Vector2 target_pos) = 0;
    virtual void attack_request_impl(Vector2 target_pos, uint64_t target_entity_id) = 0;
    virtual void ability_use_request_impl(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id) = 0;

    //Other networking methods
    void send_game_info_to(int peer_id);

    /**
     * @return Pointer to current map or nullptr if map is not set
    */
    GameLevel *get_current_level();
    GameLevel *load_game_level(const String &level_name);
};

#endif // SH_GAME_INCLUDED
