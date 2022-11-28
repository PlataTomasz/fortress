#if !defined(TUNDRA_HAS_BALL_HPP)
#define TUNDRA_HAS_BALL_HPP

#include "../../status_effect.hpp"

class TundraBall;

class TundraSpikyBallStatus : public StatusEffect
{
private:
    TundraBall *tundraBall;
public:
    //Setters/Getters
    void setBallInstance(TundraBall *tundraBall);
    TundraBall *getBallInstance();

    /**
     * Called when status wears off
    */
    virtual void onExpire()
    {

    };
    /**
     * Called when status is applied to entity
    */
    virtual void onApply();
    /**
     * Called every process frame
    */
    virtual void onProcessFrame()
    {

    };
};

#endif // TUNDRA_HAS_BALL_HPP
