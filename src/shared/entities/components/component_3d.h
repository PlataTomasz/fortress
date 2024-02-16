#if !defined(COMPONENT_3D_INCLUDED)
#define COMPONENT_3D_INCLUDED

#include <scene/3d/node_3d.h>

/**
 * Base class for all components
 * TODO: Display proper warning on missing pointers via _get_configuration_warnings
*/
class Component3D : public Node3D
{
GDCLASS(Component3D, Node3D);
private:
    
protected:

public:
    Component3D(){};
};

#endif // COMPONENT_3D_INCLUDED
