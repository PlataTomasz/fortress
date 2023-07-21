#if !defined(AAL_ABOVE_DECREE_HPP_INCLUDED)
#define AAL_ABOVE_DECREE_HPP_INCLUDED

#include <client/game_logic/damage_object.hpp>
#include <client/game_logic/abilities/passive_ability.hpp>
#include <client/game_logic/abilities/interfaces/damaging.h>

class AalDischarge : public PassiveAbility, public IDamaging
{
private:
    const static int HITS_REQUIRED = 3;

    float time_window = 2.5;

    void ready_impl() override;
    void set_owner_callback() override;
protected:
public:
    void on_entity_take_damage(Entity* ent, Ref<DamageObject> damage_object);
};

#endif // AAL_ABOVE_DECREE_HPP_INCLUDED
