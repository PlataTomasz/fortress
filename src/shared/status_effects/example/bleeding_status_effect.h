#if !defined(BLEEDING_STATUS_EFFECT_INCLUDED)
#define BLEEDING_STATUS_EFFECT_INCLUDED

#include <shared/status_effects/status_effect.hpp>

class DamageableComponent;

class BleedingStatusEffect : public StatusEffect {
GDCLASS(BleedingStatusEffect, StatusEffect);
private:
    float damage = 0;
    void _on_bleed_tick();
protected:
    virtual void _on_apply() override;
    virtual void _on_remove() override;
public:
    void set_damage(float p_damage);
    float get_damage();
};

#endif // BLEEDING_STATUS_EFFECT_INCLUDED
