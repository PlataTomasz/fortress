#if !defined(ENTITY_HPP_INCLUDED)
#define ENTITY_HPP_INCLUDED

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/visual_instance3d.hpp>
#include <godot_cpp/classes/geometry_instance3d.hpp>

using namespace godot;

/**
 * Object that is used to represent most of the beings on the GameMap
*/
class Entity : public Node3D
{
GDCLASS(Entity, Node3D);
protected:
    static void _bind_methods();
public:
    Entity();
    ~Entity();
};

#endif // ENTITY_HPP_INCLUDED