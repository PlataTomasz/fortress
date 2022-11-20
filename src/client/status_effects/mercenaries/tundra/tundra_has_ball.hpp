#if !defined(TUNDRA_HAS_BALL_HPP)
#define TUNDRA_HAS_BALL_HPP

#include "../buff_effect.hpp"
#include "../entities/mercenaries/tundra/tundra_ball.hpp"

class TundraHasBallStatus : public Buff
{
private:
    TundraBall *tundraBall;
public:
    TundraHasBallStatus();
};

#endif // TUNDRA_HAS_BALL_HPP
