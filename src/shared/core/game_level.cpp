#include "game_level.h"

void GameLevel::_init() {

}

void GameLevel::_on_enter_tree() {
    DISABLE_IN_EDITOR();

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
    entity_spawner->add_spawnable_scene("res://entities/mercenaries/Orc.tscn");
    entity_spawner->add_spawnable_scene("res://entities/mercenaries/Barbarian.tscn");
    entity_spawner->add_spawnable_scene("res://entities/box_entity.tscn");
}

Node *GameLevel::get_entities_node() {
    return entities_node;
}

void GameLevel::set_entities_node(Node *p_node) {
    entities_node = p_node;
}

void GameLevel::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_entities_node"), &GameLevel::get_entities_node);
    ::ClassDB::bind_method(D_METHOD("set_entities_node"), &GameLevel::set_entities_node);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entities_node", PROPERTY_HINT_NODE_TYPE, Node::get_class_static()), "set_entities_node", "get_entities_node");
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

Entity *GameLevel::get_entity(const String &entity_name) {
    Entity *ent = static_cast<Entity *>(entities_node->get_node_or_null(NodePath(entity_name)));
    return ent;
}