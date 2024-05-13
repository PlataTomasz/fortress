#if !defined(BLEEDING_STATUS_EFFECT_INCLUDED)
#define BLEEDING_STATUS_EFFECT_INCLUDED

#include <shared/status_effects/status_effect.hpp>

class DamageableComponent;

class BleedingStatusEffect : public StatusEffect {

private:
    DamageableComponent *damageable_component = nullptr;
    // Called when StatusEffect is applied - Effect is considered applied, when it is added to scene tree
    void _on_apply();
    void _on_remove() {

    }

    void _tick() {

    }

    // Called every "tick_timeout" seconds
    void _timed_tick() {
        // Target takes damage every 0.5 seconds
        
    }
};

#endif // BLEEDING_STATUS_EFFECT_INCLUDED
