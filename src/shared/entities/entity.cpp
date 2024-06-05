#include "entity.h"
#include <game.h>

#include <shared/entities/components/component.h>
#include <shared/core/managers/component_manager.h>

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

Node *Entity::_get_component(const String& component_typename) {
	return nullptr;
}

void Entity::_tick() {

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
			break;
		case NOTIFICATION_EXIT_TREE:
			_exit_tree();
			break;
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			break;

		default:
			break;
	}
}