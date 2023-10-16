#if !defined(SENTITY_INLCUDED)
#define SENTITY_INLCUDED

#include <scene/3d/node_3d.h>

#define S_NETWORKED_VARIABLE(type, name, id)


#define S_NETWORKED_EXISTING_VARIABLE(type, name, id)

/**
 * Serverside entity class
*/
class S_BaseEntity : public Node3D
{
GDCLASS(S_BaseEntity, Node3D);

private:
    enum NetworkedFields
    {
        NET_FIELD_POSITION = 1,
        NET_FIELD_ROTATION,
    };
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
     * Compares this and other entities.
     * @return True if both entities have the same: Position and rotation
    */
    bool is_equal(S_BaseEntity *other);
};

#endif // SENTITY_INLCUDED
