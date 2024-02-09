#if !defined(AAL_ABOVE_DECREE_HPP_INCLUDED)
#define AAL_ABOVE_DECREE_HPP_INCLUDED

#include <shared/data_holders/damage_object.hpp>
#include <shared/abilities/passive_ability.hpp>

class AalDischarge : public PassiveAbility
{
private:
    const static int HITS_REQUIRED = 3;

    float time_window = 2.5;

    void ready_impl() override;
    //Owner changed callback
    void set_owner_callback() override;
protected:
public:
    void on_entity_take_damage(Entity* ent, Ref<DamageObject> damage_object);
};

#endif // AAL_ABOVE_DECREE_HPP_INCLUDED
