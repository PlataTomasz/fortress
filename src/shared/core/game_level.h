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
protected:
	void _notification(int p_notification) {
		DISABLE_IN_EDITOR();
		switch (p_notification) {
			case NOTIFICATION_READY: {
				_ready();
			} break;

			case NOTIFICATION_POSTINITIALIZE:
				_init();
				break;

			default:
				break;
		}
	}

	void _ready() {
		DISABLE_IN_EDITOR();
		//Handling entities that are already in level
		entities_node = get_node_or_null(NodePath("Entities"));
		if (!entities_node) {
			entities_node = memnew(Node);
			entities_node->set_name("Entities");
			add_child(entities_node);
		}
	}

	void _init();
public:
	void add_entity(Entity *ent) {
		entities_node->add_child(ent);
	}

	GameLevel()
	{

	}
};

#endif // GAME_LEVEL_INCLUDED
