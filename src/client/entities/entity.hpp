#if !defined(ENTITY_HPP_INCLUDED)
#define ENTITY_HPP_INCLUDED

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/visual_instance3d.hpp>
#include <godot_cpp/classes/geometry_instance3d.hpp>
#include <godot_cpp/classes/area3d.hpp>


using namespace godot;

/**
 * Object that is used to represent most of the beings on the GameMap
 * 
 * @note Game logic happens in two dimensions, the third one is used ocassionally in special scenarios.
*/
class Entity : public Node3D
{
GDCLASS(Entity, Node3D);

private:
    /**
     * Amount of units that entity should move by with every second of movement.
    */
    unsigned int movementSpeed = 2;

    virtual void movementProcess();

    /**
     * Amount of ticks that entity will be alive.
    */
    unsigned int maxLifetime = 100;
    unsigned int currLifetime = 0;

public:
    virtual void _physics_process(double delta);
    virtual void _ready();
    void onCollision(Area3D *collider);
protected:
    static void _bind_methods();
public:
    Entity();
    ~Entity();
};

#endif // ENTITY_HPP_INCLUDED