#include <shared/abilities/barbarian/barbarian_intimidating_cry_ability.h>

void BarbarianIntimidatingCryAbility::_use(const Ref<ActionContext> &use_context) {
    ERR_FAIL_NULL(use_context->get_user());
    play_sound(use_context, intimidating_cry_use_sound);
    // TODO: Play animation
    play_vfx_at_position(warcry_vfx, use_context->get_user()->get_global_position());
}