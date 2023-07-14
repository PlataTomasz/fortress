#if !defined(TUNDRA_BALL_HPP)
#define TUNDRA_BALL_HPP

#include "../mercenary.hpp"

class TundraBall : public Entity
{
GDCLASS(TundraBall, Entity);
private:
    Entity* owner;
    /**
     * How far owner can be from this entity before it'll be forced to move toward owner?
    */
    float maxRangeFromOwner;

public:
    void onCollide(Area3D* collider);
    void _physics_process(double delta);
    void ready();
    
    void setOwner(Entity* owner)
    {
        this->owner = owner;
    }

    TundraBall()
    {
        this->maxRangeFromOwner = 0.8;
        connect("ready", callable_mp(this, &TundraBall::ready));
    };
};

#endif // TUNDRA_BALL_HPP
