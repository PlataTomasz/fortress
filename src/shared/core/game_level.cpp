#include "game_level.h"

void GameLevel::_init() {
    DISABLE_IN_EDITOR();

    NodePath entities_nodepath = NodePath();

    entity_synchronizer = memnew(MultiplayerSynchronizer);
	entity_synchronizer->set_name("EntitySynchronizer");
	add_child(entity_synchronizer);

	entity_spawner = memnew(MultiplayerSpawner);
    entity_spawner->set_name("EntitySpawner");
    add_child(entity_spawner);

    entity_spawner->set_spawn_path(entities_nodepath);

    entity_synchronizer->set_root_path(entities_nodepath);
    entity_synchronizer->set_replication_config(replication_config);

    //Add spawnable scenes
    entity_spawner->add_spawnable_scene("res://resources/entities/Mercenary.tscn");
    entity_spawner->add_spawnable_scene("res://resources/entities/Entity.tscn");
}