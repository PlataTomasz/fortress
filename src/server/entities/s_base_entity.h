#if !defined(SENTITY_INLCUDED)
#define SENTITY_INLCUDED

#include <scene/2d/node_2d.h>

/**
 * Serverside entity class
*/
class S_BaseEntity : public Node2D
{
GDCLASS(S_BaseEntity, Node2D);
private:

protected:
    
public:
    /**
     * Compares this and other entities.
     * @return True if both entities have the same: Position and rotation
    */
    bool is_equal(S_BaseEntity *other);
};

#endif // SENTITY_INLCUDED
