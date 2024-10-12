#if !defined(VISUAL_COMPONENT_3D_INCLUDED)
#define VISUAL_COMPONENT_3D_INCLUDED

#include <shared/entities/components/component_3d.h>
#include <shared/core/advanced_animation_player.h>
#include <shared/data_holders/damage_object.hpp>
#include "animation_states.h"

class MeshInstance3D;
class Entity;

//Node responsible for rendering a mesh, playing It's animations, attaching particles, etc.
class VisualComponent3D : public Component3D {
GDCLASS(VisualComponent3D, Component3D);
public:
private:
    MeshInstance3D *mesh_instance = nullptr;
    AdvancedAnimationPlayer *animation_player = nullptr;

    bool was_previously_moving = false;

    AnimationState *animation_state = nullptr;

    StringName idle_animation_name;
    StringName walk_animation_name;
    StringName death_animation_name;

    void _init();
    void _on_animation_finish(const String& animation_name);

    void _on_movement_start();
    void _on_movement_finish();
    void _on_entity_death(const Ref<DamageObject>& damage_object);
    void _on_entity_revive();
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    Entity *get_owning_entity();

    void play_animation_override(const String& animation_name);

    void play_named_animation(const StringName& animation_name);
    void play_idle_animation();
    void play_walk_animation();
    void play_death_animation();
    bool is_currently_playing_death_animation();

    void set_animation_player(AnimationPlayer *new_animation_player);
    AnimationPlayer *get_animation_player();

    void set_idle_animation_name(const StringName& new_idle_animation_name);
    StringName get_idle_animation_name();
    
    void set_walk_animation_name(const StringName& new_walk_animation_name);
    StringName get_walk_animation_name();

    void set_death_animation_name(const StringName& new_death_animation_name);
    StringName get_death_animation_name();
};

#endif // VISUAL_COMPONENT_3D_INCLUDED
