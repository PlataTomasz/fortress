#if !defined(REALM_INCLUDED)
#define REALM_INCLUDED

#include <scene/main/node.h>
#include <core/object/ref_counted.h>
#include <modules/multiplayer/scene_replication_config.h>

class Game;
class SH_Game;
class MultiplayerSynchronizer;

//Shared code for Client and Server class
class Realm : public Node {
GDCLASS(Realm, Node);
private:
    MultiplayerSynchronizer *realm_data_synchronizer = nullptr;

    Ref<SceneReplicationConfig> replication_config;

    void _ready();
    void _init();

    Node *_player_spawner(Variant &data);
protected:
    static Game *game;

    void _notification(int p_notification);
public:
    enum JoinState {
        SERVER_INFO = 1,
        CLIENT_INFO,
    };

    static Game *get_game();
    static SH_Game *get_shared_game();

    void close();
};

VARIANT_ENUM_CAST(Realm::JoinState);

#endif // REALM_INCLUDED
