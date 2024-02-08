#if !defined(TEST_MERCENARY_ABILITY)
#define TEST_MERCENARY_ABILITY

#include "ability.hpp"

//Simple passive - basic attacks deal additional damage
class TestMercenaryPassive : public Ability
{
public:
    void ready_impl() override;
    virtual void onCast();
    virtual void onTick();
    virtual void onCooldownChange();
};

#endif // TEST_MERCENARY_ABILITY
