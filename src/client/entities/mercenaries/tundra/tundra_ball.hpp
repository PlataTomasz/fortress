#if !defined(TUNDRA_BALL_HPP)
#define TUNDRA_BALL_HPP

#include "../mercenary.hpp"

class TundraBall : public Entity
{
private:
    Mercenary *owner;
    /**
     * How far owner can be from this entity before it'll be forced to move toward owner?
    */
    float maxRangeFromOwner;

    void onCollision(Area3D *collider);
    void onPhysicsFrame();
    void onReady();
public:
    TundraBall(Mercenary *owner);
};

#endif // TUNDRA_BALL_HPP
