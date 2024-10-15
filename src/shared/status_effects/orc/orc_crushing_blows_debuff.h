#if !defined(ORC_CRUSHING_BLOWS_DEBUFF_INCLUDED)
#define ORC_CRUSHING_BLOWS_DEBUFF_INCLUDED

#include <shared/status_effects/status_effect.hpp>

#include <shared/data_holders/damage_object.hpp>

class Entity;
class FloatValueModifier;

class OrcCrushingBlowsDebuff : public StatusEffect {
GDCLASS(OrcCrushingBlowsDebuff, StatusEffect);
private:
    FloatValueModifier *defense_modifier = nullptr;
protected:
    void _on_apply() override;
    void _on_remove() override;
};

#endif // ORC_CRUSHING_BLOWS_DEBUFF_INCLUDED
