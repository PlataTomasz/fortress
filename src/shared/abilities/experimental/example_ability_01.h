#if !defined(EXAMPLE_ABILITY_01_INCLUDED)
#define EXAMPLE_ABILITY_01_INCLUDED

#include <shared/abilities/ability.hpp>

class ExampleAbility01 : public Ability {
GDCLASS(ExampleAbility01, Ability);
public:
    virtual Ability::AbilityUseError use(const Ref<ActionContext>& action_context) override;

    ExampleAbility01(){};
};

#endif // EXAMPLE_ABILITY_01_INCLUDED
