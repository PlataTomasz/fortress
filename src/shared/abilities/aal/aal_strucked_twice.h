#if !defined(AAL_STRUCKED_TWICE_H_INCLUDED)
#define AAL_STRUCKED_TWICE_H_INCLUDED

#include <shared/abilities/active_ability.hpp>
#include <scene/3d/area_3d.h>

struct AbilityHitData
{
    Vector3 hit_position;
    Entity* hit_entity;
    Ability* hit_ability;
};

class AalStruckedTwice : public ActiveAbility
{
    
private:
    //How many positions remembered
    int remembered_positions = 5;

    //How far points can be from user?
    Area3D *effect_area = nullptr;


    void _use(const Ref<UseContext>& use_context);
    void on_ability_hit(const AbilityHitData& hit_data);
protected:
public:
    virtual void _ready() override;
    AalStruckedTwice();
};

#endif // AAL_STRUCKED_TWICE_H_INCLUDED
