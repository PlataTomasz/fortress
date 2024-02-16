#include "node_methods.h"

#include <core/templates/hash_set.h>
#include <core/variant/variant.h>
#include <scene/main/node.h>
#include <shared/entities/components/component.h>
#include <shared/helpers/object_ptr.h>
#include <type_traits>

//Experimental implementation - currently unused
/*
template <class T>
T *ComponentManager::get_component(Node *entity) {
	HashMap<Object *, T *> &component_cache = ComponentManager::get_component_cache<T>();

	if (cache.has()) {
		return cache.get();
	}

	//Not in cache - might be user forgot to cache it
	TypedArray<Node> children = entity->get_children();
	for (int i = 0; i < children.size(); i++) {
		if (T *obj = Object::cast_to<T>(children[i]._get_obj().obj)) {
			return obj;
		}
	}
	//Not found
	return nullptr;
};

template <class T>
void ComponentManager::add_component_to_cache(Node *entity, T *component) {
	HashMap<Object *, T *> &component_cache = ComponentManager::get_component_cache<T>();
    //Overrides older component of the same type
	component_cache.insert(entity, component);
}

template <class T>
HashMap<Node *, T *> &ComponentManager::get_component_cache() {
	//Stores information about components for each entity
	//Key is pointer to entity which has component, and Value is ObjectPtr(a pointer) to the component
	static HashMap<Node *, T *> component_cache;
	return component_cache;
}
*/