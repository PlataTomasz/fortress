#if !defined(AAL_STRAIGHT_THROUGH_HEART_H_INCLUDED)
#define AAL_STRAIGHT_THROUGH_HEART_H_INCLUDED

#include <shared/abilities/active_ability.hpp>
#include <shared/collisions/hitbox.h>

class AalStraightThroughHeart : public ActiveAbility
{
private:
    //Preload assets
    Ref<PackedScene> lightning_mesh;
    
    Area3D *hit_area = nullptr;

    //Size
    float hit_area_width = 20;
    //TODO: From API - 160 is map max size
    float hit_area_length = 160;

    void _use(const Ref<UseContext>& use_context);
    void _ready();
public:
    //Collisions
    void setup_hitboxes();
    //Render
    void setup_visuals();

    AalStraightThroughHeart();
};


#endif // AAL_STRAIGHT_THROUGH_HEART_H_INCLUDED
