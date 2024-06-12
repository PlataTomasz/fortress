#include "barbarian_basic_attack.h"

#include <scene/3d/area_3d.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/abilities/ability_caster_component.h>

class GameplayEffect {
private:
public:
    virtual void apply(Entity *target) = 0;
    virtual void undo(Entity *target) = 0;
};

// Applies damage to a target
class DamagingEffect : public GameplayEffect{
private:
    DamageType damage_type = 0;
    float damage_value = 0;
public:
    void apply(Entity *target) override {
        DamageableComponent *damageable = target->get_component<DamageableComponent>();
        damageable->take_damage();
    }

    void undo(Entity *target) override {
        
    }
};

void BarbarianBasicAttack::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_hitbox"), &BarbarianBasicAttack::get_hitbox);
    ::ClassDB::bind_method(D_METHOD("set_hitbox"), &BarbarianBasicAttack::set_hitbox);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hitbox", PROPERTY_HINT_NODE_TYPE, HitboxComponent::get_class_static()), "set_hitbox", "get_hitbox");
}

Ability::AbilityUseError BarbarianBasicAttack::use(const Ref<ActionContext>& use_context) {
    List<HitboxComponent *> hitboxes = hitbox->get_overlapping_hitboxes();

    for(HitboxComponent *detected_hitbox : hitboxes) {
        
    }
}

void BarbarianBasicAttack::set_hitbox(HitboxComponent *p_hitbox) {
    hitbox = p_hitbox;
}

HitboxComponent *BarbarianBasicAttack::get_hitbox() {
    return hitbox;
}