#include "entity.h"
#include <game.h>

#include <shared/entities/components/component.h>
#include <shared/core/managers/component_manager.h>
#include <shared/core/game_level.h>

//NOTE: That method requires Entity to be part of the SceneTree to work
void Entity::add_networked_property(const StringName &property_name) {
	ERR_FAIL_COND_MSG(is_inside_tree(), "Networked properties can only be modified if Entity is not in SceneTree!");
	networked_properties.push_back(property_name);
}

void Entity::remove_networked_property(const StringName &property_name) {
	ERR_FAIL_COND_MSG(is_inside_tree(), "Networked properties can only be modified if Entity is not in SceneTree!");
	List<StringName>::Element *e = networked_properties.find(property_name);
	if(e) {
		e->erase();
	}
}

bool Entity::has_tag(const String& tag) {
	return is_in_group(tag);
}

void Entity::add_tag(const String& tag) {
	add_to_group(tag);
}

void Entity::remove_tag(const String& tag) {
	remove_from_group(tag);
}

void Entity::_bind_methods() {
	ADD_SIGNAL(MethodInfo("hit_taken", PropertyInfo(Variant::OBJECT, "inflictor"), PropertyInfo(Variant::OBJECT, "attacker")));
	ADD_SIGNAL(MethodInfo("displayed_name_changed", PropertyInfo(Variant::STRING, "new_displayed_name")));

	::ClassDB::bind_method(D_METHOD("get_displayed_name"), &Entity::get_displayed_name);
    ::ClassDB::bind_method(D_METHOD("set_displayed_name"), &Entity::set_displayed_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "displayed_name"), "set_displayed_name", "get_displayed_name");
}

Node *Entity::_get_component(const String& component_typename) {
	return nullptr;
}

void Entity::_tick() {

}

GameLevel *Entity::get_gamelevel() {
	// FIXME: Will break if "Entity" node on GameLevel is not at 1 level of ident
	return Object::cast_to<GameLevel>(get_parent()->get_parent());
}

void Entity::_init() {
	DISABLE_IN_EDITOR();
	add_networked_property(SNAME("position"));
	add_networked_property(SNAME("rotation"));
}

void Entity::_ready() {
	DISABLE_IN_EDITOR();
	//TODO: Rather use list of all networked properties and iterate over it
}

//Cleanup
void Entity::_exit_tree() {
	DISABLE_IN_EDITOR();
	//TODO: Rather use list of all networked properties and iterate over it
	remove_networked_property(SNAME("position"));
}

void Entity::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			_readyv();
			break;
		case NOTIFICATION_EXIT_TREE:
			_exit_tree();
			break;
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			_initv();
			break;
		case NOTIFICATION_PHYSICS_PROCESS:
			_tickv();
			break;

		default:
			break;
	}
}