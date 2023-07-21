#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include <client/entities/moving_entity.hpp>
#include <client/game_logic/abilities/ability.hpp>

/**
 * Mercenary is a class responsible for representing
 * specialization of entity which is primarily supposed
 * to be controlled by Player.
*/
class Mercenary : public MovingEntity
{
GDCLASS(Mercenary, MovingEntity);

private:
    
protected:
    /**
     * [0] - Passive
     * [1, 2, 3] - Other abilities
     * [4] - Ultimate
    */
    Ability* basic_attack_ability;
    Ability* abilitySet[5];

    static void _bind_methods();
public:
    enum AbilitySetIndex
    {
        ABILITY_PASSIVE,
        ABILITY_FIRST,
        ABILITY_SECOND,
        ABILITY_THIRD,
        ABILITY_ULTIMATE,
        ABILITY_MAX
    };

    void set_ability(AbilitySetIndex abilityIndex, Ability *ability);

    void use_ability(int ability_id, UseContext& use_context);
    void use_basic_attack(UseContext& use_context);

    void initialize();
    void physics_frame();

    Mercenary();
    ~Mercenary();
};

#endif // MERCENARY_HPP_INCLUDED