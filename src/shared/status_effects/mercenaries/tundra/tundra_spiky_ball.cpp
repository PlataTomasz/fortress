#include "tundra_spiky_ball.hpp"
#include "../../../entities/mercenaries/tundra/tundra_ball.hpp"
#include "../../../game.hpp"
#include <scene/main/window.h>
#include <gdextension_helper.hpp>

TundraBall *TundraSpikyBallStatus::getBallInstance()
{
    return tundraBall;
}

void TundraSpikyBallStatus::setBallInstance(TundraBall *new_tundra_ball)
{
    this->tundraBall = new_tundra_ball;
}

void TundraSpikyBallStatus::onApply()
{
    printf("%s (TundraSpikyBall) applied!\n", this->name.ascii().get_data());
    
    //TundraBall* instance = new TundraBall(this->getTarget());
    TundraBall* instance = memnew(TundraBall);
    instance->set_owner(this->get_target());
    instance->set_name("TundraBall");
    setBallInstance(instance);
    
    Game* game = (Game*)(get_scene_tree()->get_root()->get_node(NodePath("Client/Game")));

    game->getGameMap()->addEntity(instance);
}