#include "fist_mercenary_right_punch.hpp"

void FistMercenaryRightPunchAbility::use_impl(UseContext& use_context)
{
    /*
    Deal damage and knock back enemy hit.
    If it collides with terrain, it receives additional damage
    */

    //TODO: UseTime
    Entity* target = use_context.get_target_entity();
    Entity* user = use_context.get_user();

    target->take_damage(
        Ref<DamageObject>(memnew(DamageObject(
            DAMAGE_PHYSICAL,
            100,
            user
        )))
    );

    target->apply_status_effect("fist_mercenary.armor_shred_ult_debuff", 4, user);
}

FistMercenaryRightPunchAbility::FistMercenaryRightPunchAbility()
{

}