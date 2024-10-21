#if !defined(BARBARIAN_INTIMIDATING_CRY_DEBUFF_INCLUDED)
#define BARBARIAN_INTIMIDATING_CRY_DEBUFF_INCLUDED

#include <shared/status_effects/status_effect.hpp>

class FloatValueModifier;

class BarbarianIntimidatingCryDebuff : public StatusEffect {
GDCLASS(BarbarianIntimidatingCryDebuff, StatusEffect);
private:
    FloatValueModifier *value_modifier = nullptr;
protected:
    void _on_apply() override;
    void _on_remove() override;
};

#endif // BARBARIAN_INTIMIDATING_CRY_DEBUFF_INCLUDED
