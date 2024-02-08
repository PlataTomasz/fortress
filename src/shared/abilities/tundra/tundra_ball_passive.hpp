#if !defined(TUNDRA_BALL_PASSSIVE_HPP)
#define TUNDRA_BALL_PASSSIVE_HPP

#include "../ability.hpp"

class TundraBallPassiveAbility : public Ability
{
    virtual void initialize(){};
    virtual void onCast(){};
    virtual void onTick(){};
    virtual void onCooldownChange(){};
};

#endif // TUNDRA_BALL_PASSSIVE_HPP
