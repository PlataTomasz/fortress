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
        printf("%s (TundraSpikyBall) expired!\n", this->name.ascii().get_data());
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

    bool is_permament() override
    {
        return true;
    }

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
