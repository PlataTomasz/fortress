#if !defined(ORC_LEAP_SLAM_INCLUDED)
#define ORC_LEAP_SLAM_INCLUDED

#include <shared/abilities/ability.hpp>

class OrcLeapSlam : public Ability {
GDCLASS(OrcLeapSlam, Ability);
#ifdef SERVER
protected:
    void _use(const Ref<ActionContext>& action_context);

    static void _bind_methods();
#endif
};

#endif // ORC_LEAP_SLAM_INCLUDED
