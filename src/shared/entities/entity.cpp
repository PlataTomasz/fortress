#include "entity.h"
#include <game.h>

#include <shared/entities/components/component.h>

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

void Entity::set_component(const StringName &name, Component *component) {
	set_meta(name, component);
}

template<class T>
T *Entity::get_component() {
	TypedArray<Node> components = get_children();

	for (int i = 0; i < components.size(); i++) {
		if (T *component = Object::cast_to<T>(components[i].operator Object* ())) {
			return component;
		}
	}

	return nullptr;
}

Component *Entity::get_component(const StringName &name) {
	return static_cast<Component *>(get_meta(name).operator Object *());
}

void Entity::_tick() {

}

void Entity::_init() {
	DISABLE_IN_EDITOR();
	add_networked_property(SNAME("position"));
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