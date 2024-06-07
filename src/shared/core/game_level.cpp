#include "game_level.h"

#include <shared/entities/components/hitbox/hitbox_component.h>

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

    ::ClassDB::bind_method(D_METHOD("get_entity_spawner"), &GameLevel::get_entity_spawner);
    ::ClassDB::bind_method(D_METHOD("set_entity_spawner"), &GameLevel::set_entity_spawner);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_spawner", PROPERTY_HINT_NODE_TYPE, MultiplayerSpawner::get_class_static()), "set_entity_spawner", "get_entity_spawner");

    // "what" hit "affected_entity" because of "by" - Some entity was struck by something because of some other entity
    ADD_SIGNAL(MethodInfo("entity_hit", PropertyInfo(Variant::OBJECT, "affected_entity"), PropertyInfo(Variant::OBJECT, "inflictor"), PropertyInfo(Variant::OBJECT, "attacker_entity")));
}

// Order is weird to correctly bind callable arguments
void GameLevel::_on_entity_hit(Entity *attacker, Entity *inflictor, Entity *ent) {
    // Emit level wide signal
    emit_signal("entity_hit", ent, inflictor, attacker);
}

void GameLevel::add_entity(Entity *ent) {
    // Hook into events
    HitboxComponent *hitbox = ent->get_component<HitboxComponent>();
    if(hitbox) hitbox->connect("hit", callable_mp(this, &GameLevel::_on_entity_hit).bind(ent));


	entities_node->add_child(ent);
}

Entity *GameLevel::get_entity(const String &entity_name) {
    Entity *ent = static_cast<Entity *>(entities_node->get_node_or_null(NodePath(entity_name)));
    return ent;
}