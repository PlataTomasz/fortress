#if !defined(TUNDRA_BALL_PULL_HPP)
#define TUNDRA_BALL_PULL_HPP

#include "../ability.hpp"

class TundraBallPullAbility : public Ability
{
    virtual void initialize(){};
    virtual void onCast(){};
    virtual void onTick(){};
    virtual void onCooldownChange(){};
};

#endif // TUNDRA_BALL_PULL_HPP
