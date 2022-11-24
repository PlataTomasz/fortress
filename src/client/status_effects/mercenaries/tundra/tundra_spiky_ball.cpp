#include "tundra_spiky_ball.hpp"

TundraBall *TundraSpikyBallStatusData::getBallInstance()
{
    return tundraBall;
}

void TundraSpikyBallStatusData::setBallInstance(TundraBall *tundraBall)
{
    this->tundraBall = tundraBall;
}