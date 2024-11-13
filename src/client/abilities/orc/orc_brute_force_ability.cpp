#include <shared/abilities/orc/orc_brute_force.h>

#include <scene/3d/physics/area_3d.h>

void OrcBruteForce::_use(const Ref<ActionContext> &action_context) {
    // Play punch animation
    play_animation(action_context, "Punch");

    ERR_FAIL_NULL(brute_force_area);
    play_vfx_at_position(action_context, brute_force_vfx, brute_force_area->get_position());
}