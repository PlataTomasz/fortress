#if !defined(TEST_ABILITY_HPP)
#define TEST_ABILITY_HPP

#include "ability.hpp"

class TestAbility : public Ability
{
public:
    virtual void initialize(){};
    virtual void onCast() override;
    virtual void onTick(){};
    virtual void onCooldownChange(){};
};

#endif // TEST_ABILITY_HPP
