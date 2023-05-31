#if !defined(AAL_ABOVE_DECREE_HPP_INCLUDED)
#define AAL_ABOVE_DECREE_HPP_INCLUDED

#include <client/game_logic/abilities/passive_ability.hpp>

class AalAboveDecree : public PassiveAbility
{
private:
    const static int HITS_STORED = 3;
    //Store: When hit occured, hit data
    struct FrameData
    {
        //Frame when event occured
        uint64_t frame;
        //Data associated with frame
        void* data;
    };

    //Traces recent ability hits
    Vector<FrameData> hit_registry;

    float time_window = 2.5;
protected:
public:
    void on_entity_take_damage(Entity* ent, DamageObject damageObject);
};

#endif // AAL_ABOVE_DECREE_HPP_INCLUDED
