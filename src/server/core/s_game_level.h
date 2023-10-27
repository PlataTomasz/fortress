#if !defined(S_GAME_LEVEL_INCLUDED)
#define S_GAME_LEVEL_INCLUDED

#include <scene/3d/node_3d.h>
#include <modules/multiplayer/scene_replication_config.h>
#include <modules/multiplayer/multiplayer_spawner.h>
#include <modules/multiplayer/multiplayer_synchronizer.h>
#include <server/entities/s_base_entity.h>

class S_GameLevel : public Node3D
{
GDCLASS(S_GameLevel, Node3D);
private:
	Node *entities_node;

	MultiplayerSynchronizer *mp_synchronizer;
	MultiplayerSpawner *mp_spawner;
protected:
	void _notification(int p_notification)
	{
		switch (p_notification)
		{
		case NOTIFICATION_READY:
		{
			entities_node = memnew(Node);
			entities_node->set_name("Entities");
			add_child(entities_node);

			//Setup Entity replication
			mp_synchronizer = memnew(MultiplayerSynchronizer);
			mp_synchronizer->set_name("EntitySynchronizer");
			mp_synchronizer->set_root_path(NodePath("Entities"));
			Ref<SceneReplicationConfig> mp_synchronizer_cfg = mp_synchronizer->get_replication_config();
			add_child(mp_synchronizer);

			mp_spawner = memnew(MultiplayerSpawner);
			mp_spawner->set_name("EntitySpawner");
			mp_spawner->set_spawn_path(NodePath("Entities"));
			//Add spawnable scenes
			mp_spawner->add_spawnable_scene("res://entities/entity.tscn");
			mp_spawner->add_spawnable_scene("res://entities/mercenary.tscn");

			add_child(mp_spawner);
		}
		break;

		
		
		default:
			break;
		}
	}

	virtual void add_child_notify(Node *p_child) override
	{
		if(S_BaseEntity* ent_node = Object::cast_to<S_BaseEntity>(p_child))
		{
			//Add properties to sync
			Ref<SceneReplicationConfig> mp_synchronizer_cfg = mp_synchronizer->get_replication_config();
			
			List<StringName> networked_properties = ent_node->get_networked_properties();

			//Add all networked properties
			for(int i = 0;i < networked_properties.size();i++)
			{
				//Don't know if there is better way
				NodePath property_path = String(ent_node->get_name()) + ":" + networked_properties[i];
				mp_synchronizer_cfg->add_property(property_path);
				//sync is set to false on purpose - watch is used
				mp_synchronizer_cfg->property_set_sync(property_path, false);
			}
				
		}
	}
public:
	S_GameLevel()
	{
		
	}
};

#endif // S_GAME_LEVEL_INCLUDED
