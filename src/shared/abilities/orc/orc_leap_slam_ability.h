#if !defined(ORC_LEAP_SLAM_ABILITY_INCLUDED)
#define ORC_LEAP_SLAM_ABILITY_INCLUDED

#include <shared/abilities/ability.hpp>
#include <shared/data_holders/action_context.hpp>

class Area3D;

class OrcLeapSlamAbility : public Ability {
GDCLASS(OrcLeapSlamAbility, Ability);
private:
    Area3D *leap_slam_area = nullptr;
protected:
    void _use(const Ref<ActionContext>& action_context) override;
public:
    void set_leap_slam_area(Area3D *new_leap_slam_area);
    Area3D *get_leap_slam_area();
};

#endif // ORC_LEAP_SLAM_ABILITY_INCLUDED
