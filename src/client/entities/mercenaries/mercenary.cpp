#include "mercenary.hpp"
#include "../../game_logic/abilities/test_ability.hpp"
#include "../../game_logic/abilities/throw_cube.hpp"
#include "../../game_logic/abilities/throw_ball.hpp"
#include "../../game_logic/abilities/cast_context.hpp"

Mercenary::Mercenary()
{
    skillSet[0] = new TestAbility();
    skillSet[1] = new ThrowCubeAbility();
    skillSet[2] = new ThrowBallAbility();
    skillSet[3] = new TestAbility();
    skillSet[4] = new TestAbility();
}

void Mercenary::castAbility(int abilityId, CastContext castContext)
{
    skillSet[abilityId]->setCastContext(castContext);
    skillSet[abilityId]->onCast();
}

Mercenary::~Mercenary()
{
    
}