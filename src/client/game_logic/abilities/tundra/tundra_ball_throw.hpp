#if !defined(TUNDRA_BALL_THROW_HPP)
#define TUNDRA_BALL_THROW_HPP

#include "../ability.hpp"

class TundraBallThrowAbility : public Ability
{
    virtual void initialize(){};
    virtual void onCast(){};
    virtual void onTick(){};
    virtual void onCooldownChange(){};
};

#endif // TUNDRA_BALL_THROW_HPP
