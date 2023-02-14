#include "tundra_spiky_ball.hpp"
#include "../../../entities/mercenaries/tundra/tundra_ball.hpp"
#include "../../../game.hpp"
#include <classes/window.hpp>
#include <gdextension_helper.hpp>

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
    printf("%s (TundraSpikyBall) applied!\n", this->name.ascii().get_data());
    
    //TundraBall* instance = new TundraBall(this->getTarget());
    TundraBall* instance = memnew(TundraBall);
    instance->setOwner(this->getTarget());
    instance->set_name("TundraBall");
    setBallInstance(instance);
    
    Game* game = (get_scene_tree()->get_root()->get_node<Game>(NodePath("Client/Game")));

    game->getGameMap()->addEntity(instance);
}