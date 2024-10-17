#include <shared/abilities/orc/orc_brute_force.h>

#include <scene/3d/physics/area_3d.h>

void OrcBruteForce::_use(const Ref<ActionContext> &action_context) {
    play_animation(action_context, "Attack002");

    ERR_FAIL_NULL(brute_force_area);
    ERR_FAIL_NULL(brute_force_vfx);
    play_vfx_at_position(action_context, brute_force_vfx, brute_force_area->get_position());
}