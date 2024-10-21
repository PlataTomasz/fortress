#if !defined(BARBARIAN_BARBARIC_MIGHT_ABILITY_INCLUDED)
#define BARBARIAN_BARBARIC_MIGHT_ABILITY_INCLUDED

#include <shared/abilities/ability.hpp>

class BarbarianBarbaricMightAbility : public Ability {
GDCLASS(BarbarianBarbaricMightAbility, Ability);
protected:
    void _use(const Ref<ActionContext> &use_context) override;
};

#endif // BARBARIAN_BARBARIC_MIGHT_ABILITY_INCLUDED
