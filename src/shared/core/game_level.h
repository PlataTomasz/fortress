#if !defined(GAME_LEVEL_INCLUDED)
#define GAME_LEVEL_INCLUDED

#include <scene/3d/node_3d.h>
#include <modules/multiplayer/scene_replication_config.h>
#include <modules/multiplayer/multiplayer_spawner.h>
#include <modules/multiplayer/multiplayer_synchronizer.h>

#include <shared/entities/entity.h>

//Maybe It would be better if GameLevel was entity aswell?(It could store synchronized global variables)
class GameLevel : public Node3D
{
GDCLASS(GameLevel, Node3D);
private:
	//Replication of entities on level
	MultiplayerSpawner *entity_spawner = nullptr;
	MultiplayerSynchronizer *entity_synchronizer = nullptr;

	Ref<SceneReplicationConfig> replication_config = memnew(SceneReplicationConfig);

	Node *entities_node = nullptr;

	void _on_entity_added(Node *node);
	void _on_entity_removed(Node *node);
	void _on_enter_tree();
protected:
	void _notification(int p_notification) {
		DISABLE_IN_EDITOR();
		switch (p_notification) {
			case NOTIFICATION_READY: {
				_ready();
			} break;

			case NOTIFICATION_ENTER_TREE:
				_on_enter_tree();
				break;

			case NOTIFICATION_POSTINITIALIZE:
				_init();
				break;

			default:
				break;
		}
	}

	void _ready();

	void _init();
public:
	void add_entity(Entity *ent) {
		entities_node->add_child(ent);
	}

	Entity *get_entity(const NodePath &node_path);

	GameLevel()
	{

	}
};

#endif // GAME_LEVEL_INCLUDED
