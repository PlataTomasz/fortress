#if !defined(VISUAL_COMPONENT_3D_INCLUDED)
#define VISUAL_COMPONENT_3D_INCLUDED

#include <shared/entities/components/component_3d.h>
#include <scene/animation/animation_player.h>

class MeshInstance3D;

//Node responsible for rendering a mesh, playing It's animations, attaching particles, etc.
class VisualComponent3D : public Component3D {
GDCLASS(VisualComponent3D, Component3D);
private:
    MeshInstance3D *mesh_instance = nullptr;
    AnimationPlayer *animation_player = nullptr;
    void _init();
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    void play_animation(const String& animation_name);

    void set_animation_player(AnimationPlayer *new_animation_player);
    AnimationPlayer *get_animation_player();
};

#endif // VISUAL_COMPONENT_3D_INCLUDED
