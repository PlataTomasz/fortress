#if !defined(GAME_LEVEL_INCLUDED)
#define GAME_LEVEL_INCLUDED

#include <scene/3d/node_3d.h>
#include <modules/multiplayer/scene_replication_config.h>
#include <modules/multiplayer/multiplayer_spawner.h>
#include <modules/multiplayer/multiplayer_synchronizer.h>

#include <shared/data_holders/damage_object.hpp>
#include <shared/entities/entity.h>

class Gamemode;

//Maybe It would be better if GameLevel was entity aswell?(It could store synchronized global variables)
class GameLevel : public Node3D
{
GDCLASS(GameLevel, Node3D);
private:
	//Replication of entities on level
	MultiplayerSpawner *entity_spawner = nullptr;

	Node *entities_node = nullptr;

	Gamemode *gamemode = nullptr;

	void _on_entity_hit(Entity *attacker, Entity *inflictor, Entity *ent);
	void _on_entity_damage_taken(const Ref<DamageObject>& damage_object, Entity *ent);
	void _on_entity_death(const Ref<DamageObject> &damage_object, Entity *entity);
protected:
	static void _bind_methods();
public:
	MultiplayerSpawner *get_entity_spawner() {
		return entity_spawner;
	}

	void set_entity_spawner(MultiplayerSpawner *p_entity_spawner) {
		entity_spawner = p_entity_spawner;
	}

	void add_entity(Entity *ent);

	Node *get_entities_node();
	void set_entities_node(Node *p_node);

	Entity *get_entity(const String &entity_name);

	void set_gamemode(Gamemode *new_gamemode);
	Gamemode *get_gamemode();

	GameLevel()
	{

	}
};

#endif // GAME_LEVEL_INCLUDED
