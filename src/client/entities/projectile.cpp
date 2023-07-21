#include "projectile.hpp"
#include <core/config/engine.h>

Projectile::Projectile()
{
    if(!Engine::get_singleton()->is_editor_hint())
    {
        set_physics_process(true);
    }
}

void Projectile::movementProcess()
{
    //FIXME: Assuming that game logic tickrate(aka physics tickrate) is 60 per second
    float movementSpeedPerTick = this->movementSpeed/60.0f;

    Vector3 currPos = get_position();
    auto rotation = get_rotation();

    auto angleRad = rotation.y; //Alpha angle
    //auto invertedAngleRad = M_PI - rotation.y; //Beta angle

    /*
    // This block causes entities to simulate circular movement

    auto newX = cos(invertedAngleRad)*movementSpeedPerTick;
    auto newY = sin(invertedAngleRad)*movementSpeedPerTick;
    */

    auto newX = cosf(angleRad)*movementSpeedPerTick;
    auto newZ = sinf(angleRad)*movementSpeedPerTick;

    float nextPos_x = currPos.x - newZ;
    float nextPos_z = currPos.z - newX;

    set_position(Vector3(nextPos_x, currPos.y, nextPos_z));
}

Projectile::~Projectile()
{
    
}

void Projectile::_ready()
{

}