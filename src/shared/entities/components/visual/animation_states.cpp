#include "animation_states.h"
#include <shared/entities/components/visual/visual_component_3d.h>

void IdleAnimationState::play_animation() {
    visual_component->play_idle_animation();
}
AnimationState *IdleAnimationState::on_death() {
    return new DeadAnimationState(visual_component);
}
AnimationState *IdleAnimationState::on_respawn() {
    return new IdleAnimationState(visual_component);
}
AnimationState *IdleAnimationState::on_start_walking() {
    return new WalkAnimationState(visual_component);
}
AnimationState *IdleAnimationState::on_stop_walking() {
    return new IdleAnimationState(visual_component);
}
AnimationState *IdleAnimationState::on_animation_override(const StringName& animation_name) {
    return new OverrideAnimationState(visual_component, animation_name);
}
AnimationState *IdleAnimationState::on_animation_finish() {
    return new IdleAnimationState(visual_component);
}

void WalkAnimationState::play_animation() {
    visual_component->play_walk_animation();
}
AnimationState *WalkAnimationState::on_death() {
    return new DeadAnimationState(visual_component);
}
AnimationState *WalkAnimationState::on_respawn() {
    return new WalkAnimationState(visual_component);
}
AnimationState *WalkAnimationState::on_start_walking() {
    return new WalkAnimationState(visual_component);
}
AnimationState *WalkAnimationState::on_stop_walking() {
    return new IdleAnimationState(visual_component);
}
AnimationState *WalkAnimationState::on_animation_override(const StringName& animation_name) {
    return new OverrideAnimationState(visual_component, animation_name);
}
AnimationState *WalkAnimationState::on_animation_finish() {
    return new WalkAnimationState(visual_component);
}

void DeadAnimationState::play_animation() {
    if(!already_played) {
        visual_component->play_death_animation();
        already_played = true;
    }
}
AnimationState *DeadAnimationState::on_death() {
    return new DeadAnimationState(*this);
}
AnimationState *DeadAnimationState::on_respawn() {
    return new IdleAnimationState(visual_component);
}
AnimationState *DeadAnimationState::on_start_walking() {
    return new DeadAnimationState(*this);
}
AnimationState *DeadAnimationState::on_stop_walking() {
    return new DeadAnimationState(*this);
}
AnimationState *DeadAnimationState::on_animation_override(const StringName& animation_name) {
    return new DeadAnimationState(*this);
}
AnimationState *DeadAnimationState::on_animation_finish() {
    return new DeadAnimationState(*this);
}

void OverrideAnimationState::play_animation() {
    visual_component->play_named_animation(animation_name_to_play);
}
AnimationState *OverrideAnimationState::on_death() {
    return new DeadAnimationState(visual_component);
}
AnimationState *OverrideAnimationState::on_respawn() {
    return new OverrideAnimationState(visual_component, animation_name_to_play);
}
AnimationState *OverrideAnimationState::on_start_walking() {
    return new WalkAnimationState(visual_component);
}
AnimationState *OverrideAnimationState::on_stop_walking() {
    return new OverrideAnimationState(visual_component, animation_name_to_play);
}
AnimationState *OverrideAnimationState::on_animation_override(const StringName& animation_name) {
    return new OverrideAnimationState(visual_component, animation_name);
}
AnimationState *OverrideAnimationState::on_animation_finish() {
    return new IdleAnimationState(visual_component);
}