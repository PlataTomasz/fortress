#if !defined(TURRET_ATTACK_ABILITY_INCLUDED)
#define TURRET_ATTACK_ABILITY_INCLUDED

#include <shared/abilities/ability.hpp>
#include <scene/resources/packed_scene.h>

class TurretAttackAbility : public Ability {
GDCLASS(TurretAttackAbility, Ability);
private:
    Ref<PackedScene> turret_projectile_template;
protected:
    virtual void _use(const Ref<ActionContext>& action_context) override;
};

#endif // TURRET_ATTACK_ABILITY_INCLUDED
