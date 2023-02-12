#if !defined(TUNDRA_BALL_HPP)
#define TUNDRA_BALL_HPP

#include "../mercenary.hpp"

class TundraBall : public Entity
{
private:
    Entity* owner;
    /**
     * How far owner can be from this entity before it'll be forced to move toward owner?
    */
    float maxRangeFromOwner;

    void onCollide(Area3D* collider);
    void _physics_process(double delta) override;
    void _ready() override;

    static void _bind_methods();
public:
    TundraBall(Entity* owner);
};

#endif // TUNDRA_BALL_HPP
