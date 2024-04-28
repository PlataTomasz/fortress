#if !defined(TEST_ABILITY_HPP)
#define TEST_ABILITY_HPP

#include "ability.hpp"

class TestAbility : public Ability
{
GDCLASS(TestAbility, Ability);
public:
    void _use(const Ref<ActionContext>& action_context);
    TestAbility();
};

#endif // TEST_ABILITY_HPP
