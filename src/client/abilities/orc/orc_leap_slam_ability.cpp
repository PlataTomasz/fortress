#include <shared/abilities/orc/orc_leap_slam_ability.h>

#include <scene/animation/tween.h>
#include <scene/main/timer.h>
#include <shared/core/game_level.h>

void OrcLeapSlamAbility::_use(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(action_context->get_user());
    ERR_FAIL_NULL(slam_vfx);

    Timer *timer = memnew(Timer);
    timer->set_wait_time(0.5);
    timer->set_autostart(true);
    timer->connect("timeout", callable_mp(this, &OrcLeapSlamAbility::_slam).bind(action_context, action_context->get_user()->get_global_position()));
    timer->connect("timeout", callable_mp((Node *)timer, &Node::queue_free));
    add_child(timer);
}

void OrcLeapSlamAbility::_slam(const Ref<ActionContext>& action_context, const Vector3 &slam_position) {
    Node3D *vfx_instance = Object::cast_to<Node3D>(slam_vfx->instantiate());
    ERR_FAIL_NULL(vfx_instance);
    ERR_FAIL_NULL(action_context->get_user()->get_gamelevel());
    action_context->get_user()->get_gamelevel()->add_child(vfx_instance);

    vfx_instance->set_global_position(slam_position);
}