#include "entity.h"

#ifdef SERVER
	#include <server/core/game.h>
	#include <server/server.h>
#else
	#include <client/game.hpp>
	#include <client/client.hpp>
#endif

void Entity::add_networked_property(const StringName &property_name) {
	//NOTE: That method will crash if there is not Game node!
	//UGLY!
	#ifdef SERVER
		Server::get_game()->add_node_networked_property(this, property_name);
	#else
		Client::get_game()->add_node_networked_property(this, property_name);
	#endif
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

void Entity::_tick() {

}

void Entity::_ready() {
	DISABLE_IN_EDITOR();
	add_networked_property(SNAME("position"));
}

void Entity::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			break;
		default:
			break;
	}
}