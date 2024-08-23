#if !defined(VISUAL_COMPONENT_3D_INCLUDED)
#define VISUAL_COMPONENT_3D_INCLUDED

#include <shared/entities/components/component_3d.h>
#include <shared/core/advanced_animation_player.h>

class MeshInstance3D;
class Entity;

//Node responsible for rendering a mesh, playing It's animations, attaching particles, etc.
class VisualComponent3D : public Component3D {
GDCLASS(VisualComponent3D, Component3D);
public:
    enum AnimationState {
        IDLE,
        WALK,
        OVERRIDE,
        ANIMATION_STATE_MAX
    };
private:
    MeshInstance3D *mesh_instance = nullptr;
    AdvancedAnimationPlayer *animation_player = nullptr;

    bool was_previously_moving = false;

    AnimationState animation_state = AnimationState::IDLE;

    void _init();
    void _on_animation_finish(const String& animation_name);

    void _on_owner_movement_state_change(bool is_moving);
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    Entity *get_owning_entity();

    void play_animation_override(const String& animation_name);
    void switch_to_idle_animation();
    void switch_to_walk_animation();

    void set_animation_player(AnimationPlayer *new_animation_player);
    AnimationPlayer *get_animation_player();
};

#endif // VISUAL_COMPONENT_3D_INCLUDED
