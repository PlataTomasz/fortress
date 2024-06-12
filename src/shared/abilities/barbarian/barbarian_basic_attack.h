#if !defined(BARBARIAN_BASIC_ATTACK_INCLUDED)
#define BARBARIAN_BASIC_ATTACK_INCLUDED

#include <core/object/ref_counted.h>
#include <shared/data_holders/action_context.hpp>
#include <shared/abilities/basic_attack.h>

#include <shared/entities/components/hitbox/hitbox_component.h>

class Area3D;

class BarbarianBasicAttack : public BasicAttack {
GDCLASS(BarbarianBasicAttack, BasicAttack);
private:
    float damage = 0;
    HitboxComponent *hitbox = nullptr;
protected:
    void BarbarianBasicAttack::_bind_methods();
public:
    Ability::AbilityUseError use(const Ref<ActionContext>& use_context);

    void set_hitbox(HitboxComponent *p_hitbox);
    HitboxComponent *get_hitbox();
};

#endif // BARBARIAN_BASIC_ATTACK_INCLUDED
