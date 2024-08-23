#if !defined(ADVANCED_ANIMATION_PLAYER)
#define ADVANCED_ANIMATION_PLAYER

#include <scene/animation/animation_player.h>

class AdvancedAnimationPlayer : public AnimationPlayer {
GDCLASS(AdvancedAnimationPlayer, AnimationPlayer);
public:
    void play_animation_from_any_library(const String& animation_name);
    void queue_from_any_library(const String& animation_name);
};

#endif // ADVANCED_ANIMATION_PLAYER
