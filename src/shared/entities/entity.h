#if !defined(ENTITY_INCLUDED)
#define ENTITY_INCLUDED

#include <scene/3d/node_3d.h>
#include <scene/main/multiplayer_api.h>
#include <server/server.h>

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

	void _init();
	void _ready();
	void _tick();
	
	void _exit_tree();

protected:
	void _notification(int p_notification);
public:
	Vector2 get_position_2d() {
		Vector3 pos = get_position();
		return Vector2(pos.x, pos.z);
	}

	float get_rotation_2d() {
		return get_rotation().y;
	}

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

	template <class T>
	T *get_component();
};

#endif // ENTITY_INCLUDED
