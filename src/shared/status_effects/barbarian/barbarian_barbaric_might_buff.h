#if !defined(BARBARIAN_BARBARIC_MIGHT_INCLUDED)
#define BARBARIAN_BARBARIC_MIGHT_INCLUDED

#include <shared/status_effects/status_effect.hpp>
#include <shared/data_holders/damage_object.hpp>

class Entity;
class BasicAttack;

class BarbarianBarbaricMightBuff : public StatusEffect {
GDCLASS(BarbarianBarbaricMightBuff, StatusEffect);
private:
    void _on_basic_attack_damage(const Ref<DamageObject> damage_object, Entity *target);
protected:
    void _on_apply();
    void _on_remove();
};

#endif // BARBARIAN_BARBARIC_MIGHT_INCLUDED
