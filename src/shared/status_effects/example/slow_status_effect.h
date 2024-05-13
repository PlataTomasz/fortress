#if !defined(SLOW_STATUS_EFFECT_H)
#define SLOW_STATUS_EFFECT_H

#include <shared/status_effects/status_effect.hpp>
#include <shared/entities/components/entity_stats/float_attribute.h>


class SlowStatusEffect : public StatusEffect {
GDCLASS(SlowStatusEffect, StatusEffect);
protected:
    Ref<FloatValueModifier> modifier;

    void _on_apply() override;
    void _on_remove() override;
};

#endif // SLOW_STATUS_EFFECT_H
