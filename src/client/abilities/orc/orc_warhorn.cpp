#include <shared/abilities/orc/orc_warhorn.h>

#include <shared/entities/components/visual/visual_component_3d.h>

void OrcWarhornAbility::_use(const Ref<ActionContext> &action_context) {
    play_sound(action_context, warhorn_audio);
    play_animation(action_context, "WarhornUse");
    play_vfx(action_context, warhorn_vfx);
}