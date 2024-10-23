#if !defined(ORC_LEAP_SLAM_ABILITY_INCLUDED)
#define ORC_LEAP_SLAM_ABILITY_INCLUDED

#include <shared/abilities/ability.hpp>
#include <shared/data_holders/action_context.hpp>

class Area3D;

class OrcLeapSlamAbility : public Ability {
GDCLASS(OrcLeapSlamAbility, Ability);
private:
    Area3D *leap_slam_area = nullptr;
    Ref<PackedScene> slam_vfx;

    void _slam(const Ref<ActionContext>& action_context, const Vector3 &slam_position);
protected:
    void _use(const Ref<ActionContext>& action_context) override;
    static void _bind_methods();
public:
    void set_leap_slam_area(Area3D *new_leap_slam_area);
    Area3D *get_leap_slam_area();

    void set_slam_vfx(const Ref<PackedScene> &new_slam_vfx);
    Ref<PackedScene> get_slam_vfx();
};

#endif // ORC_LEAP_SLAM_ABILITY_INCLUDED
