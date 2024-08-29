#include "game_level.h"

#include <shared/entities/components/hitbox/hitbox_component.h>
#include <shared/entities/components/damage/damageable_component.h>

#include <shared/gamemodes/gamemode.h>

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

    ::ClassDB::bind_method(D_METHOD("get_gamemode"), &GameLevel::get_gamemode);
    ::ClassDB::bind_method(D_METHOD("set_gamemode"), &GameLevel::set_gamemode);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gamemode", PROPERTY_HINT_NODE_TYPE, Gamemode::get_class_static()), "set_gamemode", "get_gamemode");

    // "what" hit "affected_entity" because of "by" - Some entity was struck by something because of some other entity
    ADD_SIGNAL(MethodInfo("entity_hit", PropertyInfo(Variant::OBJECT, "affected_entity"), PropertyInfo(Variant::OBJECT, "inflictor"), PropertyInfo(Variant::OBJECT, "attacker_entity")));

    ADD_SIGNAL(MethodInfo("entity_damage_taken", PropertyInfo(Variant::OBJECT, "entity"), PropertyInfo(Variant::OBJECT, "damage_object")));

    ADD_SIGNAL(MethodInfo("entity_added", PropertyInfo(Variant::OBJECT, "entity")));
}

// Order is weird to correctly bind callable arguments
void GameLevel::_on_entity_hit(Entity *attacker, Entity *inflictor, Entity *ent) {
    // Emit level wide signal
    emit_signal("entity_hit", ent, inflictor, attacker);
}

void GameLevel::_on_entity_damage_taken(const Ref<DamageObject>& damage_object, Entity *ent) {
    // Emit level wide signal
    emit_signal("entity_damage_taken", damage_object, ent);
}

void GameLevel::add_entity(Entity *ent) {
    // Hook into events if possible
    HitboxComponent *hitbox = ent->get_component<HitboxComponent>();
    if(hitbox) hitbox->connect("hit", callable_mp(this, &GameLevel::_on_entity_hit).bind(ent));

    DamageableComponent *damageable = ent->get_component<DamageableComponent>();
    if(damageable) damageable->connect("damage_taken", callable_mp(this, &GameLevel::_on_entity_damage_taken).bind(ent));

	entities_node->add_child(ent);
    emit_signal("entity_added", ent);
}

Entity *GameLevel::get_entity(const String &entity_name) {
    Entity *ent = Object::cast_to<Entity>(entities_node->get_node_or_null(NodePath(entity_name)));
    return ent;
}

void GameLevel::set_gamemode(Gamemode *new_gamemode) {
    gamemode = new_gamemode;
}

Gamemode *GameLevel::get_gamemode() {
    return gamemode;
}