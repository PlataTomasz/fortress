#include "tundra_spiky_ball.hpp"
#include "../../../entities/mercenaries/tundra/tundra_ball.hpp"
#include "../../../entity_manager.hpp"

TundraBall *TundraSpikyBallStatus::getBallInstance()
{
    return tundraBall;
}

void TundraSpikyBallStatus::setBallInstance(TundraBall *tundraBall)
{
    this->tundraBall = tundraBall;
}

void TundraSpikyBallStatus::onApply()
{
    TundraBall *instance = new TundraBall(this->getTarget());
    setBallInstance(instance);
    
    EntityManager;
}