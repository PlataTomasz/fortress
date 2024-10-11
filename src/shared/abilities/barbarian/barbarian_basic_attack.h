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

    Ref<PackedScene> hit_visual_effect;
    Ref<PackedScene> attack_area_vfx;

    void _prepare_attack(const Ref<ActionContext>& use_context);
    void _entity_hit_with_attack(Entity *entity, const Ref<ActionContext>& use_context);
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

    void set_hit_visual_effect(const Ref<PackedScene> &new_hit_visual_effect);
    Ref<PackedScene> get_hit_visual_effect();

    void set_attack_area_vfx(const Ref<PackedScene> &new_attack_area_vfx);
    Ref<PackedScene> get_attack_area_vfx();
};

#endif // BARBARIAN_BASIC_ATTACK_INCLUDED
