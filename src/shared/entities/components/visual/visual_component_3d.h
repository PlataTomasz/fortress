#if !defined(VISUAL_COMPONENT_3D_INCLUDED)
#define VISUAL_COMPONENT_3D_INCLUDED

#include <shared/entities/components/component_3d.h>

class MeshInstance3D;

//Node responsible for rendering a mesh, playing It's animations, attaching particles, etc.
class VisualComponent3D : public Component3D {
GDCLASS(VisualComponent3D, Component3D);
private:
    MeshInstance3D *mesh_instance_3d = nullptr;
    void _init();
protected:
    void _notification(int p_notification);
};

#endif // VISUAL_COMPONENT_3D_INCLUDED
