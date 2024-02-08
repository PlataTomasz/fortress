#if !defined(TUNDRA_HAMMER_THROW_HPP)
#define TUNDRA_HAMMER_THROW_HPP

#include "../ability.hpp"

class TundraHammerThrowAbility : public Ability
{
    virtual void initialize(){};
    virtual void onCast(){};
    virtual void onTick(){};
    virtual void onCooldownChange(){};
};

#endif // TUNDRA_HAMMER_THROW_HPP
