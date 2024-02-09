#if !defined(ENTITY_INCLUDED)
#define ENTITY_INCLUDED

#include <scene/3d/node_3d.h>
#include <scene/main/multiplayer_api.h>
#include <server/server.h>
#include <shared/entities/node_methods.h>

/**
 * Base class for representing most of the in-game objects, such as projectiles, monsters, ticking entities
*/
class Entity : public Node3D
{
GDCLASS(Entity, Node3D);

private:
	/**
	 * Stores names of all properties that should be networked
	*/
	List<StringName> networked_properties;
protected:

public:
    Vector2 get_position_2d()
    {
        Vector3 pos = get_position();
        return Vector2(pos.x, pos.z);
    }

    float get_rotation_2d()
    {
        return get_rotation().y;
    }

	/**
	 * Returns a list of all properties that should be networked
	*/
	List<StringName> get_networked_properties()
	{
		return networked_properties;
	}

    void add_networked_property(StringName property_name);

    Entity()
    {
        //Networked properties
        add_networked_property("position");
        add_networked_property("rotation");
    }

    /**
     * Compares this and other entities.
     * @return True if both entities have the same: Position and rotation
    */
    bool is_equal(Entity *other);

    template<class T>
    T *get_component(StringName component_name)
    {
        return EntityGlobals::get_component<T>(this, component_name);
    }
};

#endif // ENTITY_INCLUDED
