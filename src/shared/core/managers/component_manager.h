#if !defined(COMPONENT_MANAGER_INCLUDED)
#define COMPONENT_MANAGER_INCLUDED

#include <core/object/object.h>
#include <scene/main/node.h>

// Allows to easily find component on given node
class ComponentManager : public Object {
public:
	// Returns given component of node if it exists. IF more components exits - The first found is used
	template <class T>
	static T * get_component(Node *component_holder) {
		T *component = nullptr;
		TypedArray<Node> component_holder_children = component_holder->get_children();

		for (int i = 0; i < component_holder_children.size() && component == nullptr; i++) {
			component = Object::cast_to<T>(component_holder_children[i].operator Object *());
		}

		return component;
	};
};

#endif // COMPONENT_MANAGER_INCLUDED
