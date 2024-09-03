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

    void _reparent_hitbox();
protected:
#ifdef CLIENT
    virtual void _clientside_use(const Ref<ActionContext>& action_context) override;
#endif

    void _notification(int p_notification);
    static void _bind_methods();
public:
    void _use(const Ref<ActionContext>& use_context);

    void set_hitbox(HitboxComponent *p_hitbox);
    HitboxComponent *get_hitbox();
};

#endif // BARBARIAN_BASIC_ATTACK_INCLUDED
