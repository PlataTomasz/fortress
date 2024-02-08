#if !defined(TEST_ABILITY_HPP)
#define TEST_ABILITY_HPP

#include "ability.hpp"

class TestAbility : public Ability
{
GDCLASS(TestAbility, Ability);
public:
    void use_impl(UseContext& use_context) override;
    TestAbility();
};

#endif // TEST_ABILITY_HPP
