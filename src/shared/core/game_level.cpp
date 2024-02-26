#include "game_level.h"

void GameLevel::_init() {
    DISABLE_IN_EDITOR();

    NodePath entities_nodepath = NodePath("../Entities");

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

void GameLevel::_ready() {
    DISABLE_IN_EDITOR();
    //Handling entities that are already in level
    entities_node = get_node_or_null(NodePath("Entities"));
    if (!entities_node) {
        entities_node = memnew(Node);
        entities_node->set_name("Entities");
        add_child(entities_node);
    }
    entities_node->connect("child_entered_tree", callable_mp(this, &GameLevel::_on_entity_added));
    entities_node->connect("child_exiting_tree", callable_mp(this, &GameLevel::_on_entity_removed));
}

// That code below might be extremly slow, but there is no other way I'm aware of
void GameLevel::_on_entity_added(Node *node) {
	if (Entity *ent = Object::cast_to<Entity>(node)) {
		// Add all networked properties
		List<StringName> &net_properties = ent->get_networked_properties();
		for (int i = 0; i < net_properties.size(); i++) {
			NodePath property_path = NodePath(String(ent->get_name()) + ":" + String(net_properties[i]));
			replication_config->add_property(property_path);
			replication_config->property_set_watch(property_path, true);
			replication_config->property_set_sync(property_path, false);
		}
	}
}

void GameLevel::_on_entity_removed(Node *node) {
    if(Entity *ent = Object::cast_to<Entity>(node)) {
        // Remove all networked properties
        List<StringName> &net_properties = ent->get_networked_properties();
        for (int i = 0; i < net_properties.size(); i++) {
            NodePath property_path = NodePath(String(ent->get_name()) + ":" + String(net_properties[i]));
            replication_config->remove_property(property_path);
        }
    }
}

Entity *GameLevel::get_entity(const NodePath &node_path) {
    Entity *ent = static_cast<Entity *>(get_node_or_null(node_path));
    return ent;
}