#if !defined(TUNDRA_HAS_BALL_HPP)
#define TUNDRA_HAS_BALL_HPP

#include "../../status_effect.hpp"

class TundraBall;

//TODO: Replace with (MiscStatusEffect : StatusEffect)
class TundraSpikyBallStatusData : public StatusEffectData
{
private:
    TundraBall *tundraBall;
public:
    void setBallInstance(TundraBall *tundraBall);
    TundraBall *getBallInstance();
};

class TundraSpikyBallStatusScript : public StatusEffectScript
{
public:
    /**
     * Called when status wears off
    */
    virtual void onExpire()
    {

    };
    /**
     * Called when status is applied to entity
    */
    virtual void onApply()
    {

    };
    /**
     * Called every process frame
    */
    virtual void onProcessFrame()
    {

    };
};

#endif // TUNDRA_HAS_BALL_HPP
