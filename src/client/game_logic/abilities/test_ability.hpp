#if !defined(TEST_ABILITY_HPP)
#define TEST_ABILITY_HPP

#include <client/game_logic/abilities/ability.hpp>

class TestAbility : public Ability
{

public:
    void use_impl(UseContext& use_context) override;
    TestAbility();
};

#endif // TEST_ABILITY_HPP
