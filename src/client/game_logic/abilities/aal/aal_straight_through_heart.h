#if !defined(AAL_STRAIGHT_THROUGH_HEART_H_INCLUDED)
#define AAL_STRAIGHT_THROUGH_HEART_H_INCLUDED

#include <client/game_logic/abilities/active_ability.hpp>

class AalStraightThroughHeart : public ActiveAbility
{
private:
    //Preload assets
    Ref<PackedScene> lightning_mesh;

    Area3D* hit_area = nullptr;

    void use_impl(UseContext use_context) override;
public:
    AalStraightThroughHeart();
};


#endif // AAL_STRAIGHT_THROUGH_HEART_H_INCLUDED
