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


	Node *entities_node = nullptr;
protected:
	void _notification(int p_notification) {
		DISABLE_IN_EDITOR();
		switch (p_notification) {
			case NOTIFICATION_READY: {
				_ready();
			} break;

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

public:
	GameLevel()
	{

	}
};

#endif // GAME_LEVEL_INCLUDED
