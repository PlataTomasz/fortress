#if !defined(TUNDRA_HAS_BALL_HPP)
#define TUNDRA_HAS_BALL_HPP

#include "../../status_effect.hpp"

class TundraBall;

class TundraSpikyBallStatus : public StatusEffect
{
VIRTUAL_COPY(TundraSpikyBallStatus);

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
        printf("%s (TundraSpikyBall) expired!\n", this->name.ascii().ptr());
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

    TundraSpikyBallStatus(Dictionary dict) : StatusEffect(dict)
    {
        
    }

    TundraSpikyBallStatus()
    {

    }

    ~TundraSpikyBallStatus()
    {
        
    }
};

#endif // TUNDRA_HAS_BALL_HPP
