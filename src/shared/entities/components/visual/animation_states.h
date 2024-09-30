#if !defined(ANIMATION_STATES_INCLUDED)
#define ANIMATION_STATES_INCLUDED

#include <scene/animation/animation_player.h>

class VisualComponent3D;

class AnimationState {
protected:
    VisualComponent3D *visual_component = nullptr;
public:
    virtual void play_animation() = 0;
	virtual AnimationState *on_death() = 0;
	virtual AnimationState *on_respawn() = 0;
	virtual AnimationState *on_start_walking() = 0;
	virtual AnimationState *on_stop_walking() = 0;
	virtual AnimationState *on_animation_override(const StringName& animation_name) = 0;
	virtual AnimationState *on_animation_finish(bool is_walking) = 0;
	// TODO: When animation finishes in override state, it should move into either idle, movement or death based on current

    AnimationState(VisualComponent3D *new_visual_component) {
        visual_component = new_visual_component;
    };
};

class WalkAnimationState : public AnimationState {
public:
    virtual void play_animation() override;
	virtual AnimationState *on_death() override;
	virtual AnimationState *on_respawn() override;
	virtual AnimationState *on_start_walking() override;
	virtual AnimationState *on_stop_walking() override;
	virtual AnimationState *on_animation_override(const StringName& animation_name) override;
	virtual AnimationState *on_animation_finish(bool is_walking) override;

    WalkAnimationState(VisualComponent3D *new_visual_component) : AnimationState(new_visual_component) {
        
    }
};

class IdleAnimationState : public AnimationState {
public:
    virtual void play_animation() override;
    virtual AnimationState *on_death() override;
	virtual AnimationState *on_respawn() override;
	virtual AnimationState *on_start_walking() override;
	virtual AnimationState *on_stop_walking() override;
	virtual AnimationState *on_animation_override(const StringName& animation_name) override;
	virtual AnimationState *on_animation_finish(bool is_walking) override;

    IdleAnimationState(VisualComponent3D *new_visual_component) : AnimationState(new_visual_component) {

    }
};

class DeadAnimationState : public AnimationState {
private:
    bool already_played = false;
public:
    virtual void play_animation() override;
    virtual AnimationState *on_death() override;
	virtual AnimationState *on_respawn() override;
	virtual AnimationState *on_start_walking() override;
	virtual AnimationState *on_stop_walking() override;
	virtual AnimationState *on_animation_override(const StringName& animation_name) override;
	virtual AnimationState *on_animation_finish(bool is_walking) override;

    DeadAnimationState(VisualComponent3D *new_visual_component) : AnimationState(new_visual_component) {

    }
    
    // DeadAnimationState(DeadAnimationState *from) : AnimationState(from->visual_component) {
    //     already_played = from->already_played;
    // }
};

class OverrideAnimationState : public AnimationState {
private:
    StringName animation_name_to_play;
public:
    virtual void play_animation() override;
    virtual AnimationState *on_death() override;
	virtual AnimationState *on_respawn() override;
	virtual AnimationState *on_start_walking() override;
	virtual AnimationState *on_stop_walking() override;
	virtual AnimationState *on_animation_override(const StringName& animation_name) override;
	virtual AnimationState *on_animation_finish(bool is_walking) override;

    OverrideAnimationState(VisualComponent3D *new_visual_component, const StringName& animation_name) : AnimationState(new_visual_component) {
        animation_name_to_play = animation_name;
    }
};

#endif // ANIMATION_STATES_INCLUDED
