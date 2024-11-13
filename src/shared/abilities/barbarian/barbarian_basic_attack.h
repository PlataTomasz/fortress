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

    Node3D *slash_vfx_origin = nullptr;
    Ref<AudioStream> attack_sound;

    float range = 2;

    void _prepare_attack(const Ref<ActionContext>& use_context);
    void _entity_hit_with_attack(Entity *entity, const Ref<ActionContext>& use_context);
protected:
    virtual void _use(const Ref<ActionContext>& action_context) override;

    void _notification(int p_notification);
    static void _bind_methods();
public:

    void set_hitbox(HitboxComponent *p_hitbox);
    HitboxComponent *get_hitbox();

    void set_hit_visual_effect(const Ref<PackedScene> &new_hit_visual_effect);
    Ref<PackedScene> get_hit_visual_effect();

    void set_attack_area_vfx(const Ref<PackedScene> &new_attack_area_vfx);
    Ref<PackedScene> get_attack_area_vfx();

    void set_range(float new_range);
    float get_range();

    void set_slash_vfx_origin(Node3D *new_slash_vfx_origin);
    Node3D *get_slash_vfx_origin();

    void set_attack_sound(const Ref<AudioStream> &new_attack_sound);
    Ref<AudioStream> get_attack_sound();
};

#endif // BARBARIAN_BASIC_ATTACK_INCLUDED
