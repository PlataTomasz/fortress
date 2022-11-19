#include "tundra_ball.hpp"

TundraBall::TundraBall(Mercenary *owner)
{
    if(!Engine::get_singleton()->is_editor_hint())
    {
        this->owner = owner;

        connect("ready", callable_mp(this, &TundraBall::onReady));
        connect("area_entered", callable_mp(this, &TundraBall::onCollision));
    }
}

void TundraBall::onCollision(Area3D *collider)
{
    //Deal damage when the ball moved into other entity as a result of other ability or result of displacement toward ball

    /*
    Pseudocode:
    - If collider is under displacement effect or ball final position was result of ability, deal damage to them
    */

}

void TundraBall::onPhysicsFrame()
{
    //Get owner position and move toward him if It's too far away
    Vector3 ballPos = this->get_position();
    if(ballPos.distance_to(owner->get_position()) > maxRangeFromOwner)
    {
        //TODO: Prevent position updates if Tundra is currently casting ability
        //if(owner.isCurrentlyCastingAbility)?
        //Signal position change and tie ball position update to owner position changes?

    }
}