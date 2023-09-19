#if !defined(TEST_ABILITY_2_HPP)
#define TEST_ABILITY_2_HPP

#include <client/game_logic/abilities/ability.hpp>

class TestAbility2 : public Ability
{
GDCLASS(TestAbility2, Ability);
public:
    void use_impl(UseContext& use_context) override;
    TestAbility2();
};

#endif // TEST_ABILITY_2_HPP
