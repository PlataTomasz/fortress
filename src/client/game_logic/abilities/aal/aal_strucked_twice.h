#if !defined(AAL_STRUCKED_TWICE_H_INCLUDED)
#define AAL_STRUCKED_TWICE_H_INCLUDED

#include <client/game_logic/abilities/active_ability.hpp>

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
    Area3D* effect_area = nullptr;


    void use_impl(UseContext& use_context) override;
    void on_ability_hit(const AbilityHitData& hit_data);
protected:
public:
    void ready_impl() override;
    AalStruckedTwice();
};

#endif // AAL_STRUCKED_TWICE_H_INCLUDED
