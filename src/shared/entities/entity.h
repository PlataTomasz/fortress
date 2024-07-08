#if !defined(ENTITY_INCLUDED)
#define ENTITY_INCLUDED

#include <scene/3d/node_3d.h>
#include <scene/main/multiplayer_api.h>
#include <server/server.h>

class GameLevel;

/**
 * Base class for representing most of the in-game objects, such as projectiles, monsters, ticking entities
 */
class Entity : public Node3D {
	GDCLASS(Entity, Node3D);

private:
	/**
	 * Stores names of all properties that should be networked
	 */
	List<StringName> networked_properties;

	// Name which is displayed by the UI
	String displayed_name;

	void _init();
	void _ready();
	void _tick();

	void _exit_tree();

protected:
	virtual Node *_get_component(const String& component_typename);

	void _notification(int p_notification);

	static void _bind_methods();
public:
	Vector2 get_position_2d() {
		Vector3 pos = get_position();
		return Vector2(pos.x, pos.z);
	}

	float get_rotation_2d() {
		return get_rotation().y;
	}

	String get_displayed_name() {
		return displayed_name;
	}

	void set_displayed_name(const String& p_displayed_name) {
		displayed_name = p_displayed_name;
		emit_signal("displayed_name_changed", p_displayed_name);
	}

	// Returns level where this entity is
	GameLevel *get_gamelevel();

	/**
	 * Returns a list of all properties that should be networked
	 */
	List<StringName> &get_networked_properties() {
		return networked_properties;
	}

	void add_networked_property(const StringName &property_name);
	void remove_networked_property(const StringName &property_name);

	Entity() {
	}

	
	template<class T>
	T *get_component() {
		return Object::cast_to<T>(_get_component(T::get_class_static()));
	}
};

#endif // ENTITY_INCLUDED
