#if !defined(ENTITY_INFO_RENDERER)
#define ENTITY_INFO_RENDERER

#include <scene/3d/node_3d.h>

/**
 * Class responsible for rendering entity info in 3d space, such as health and status effects inflicted on entity
 */
class EntityInfoRenderer : public Node3D {
GDCLASS(EntityInfoRenderer, Node3D);
private:

protected:
    void _notification(int p_notification);
public:
    void _ready();
};

#endif // ENTITY_INFO_RENDERER
