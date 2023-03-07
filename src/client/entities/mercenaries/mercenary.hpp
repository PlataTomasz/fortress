#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include <client/entities/entity.hpp>
#include <client/game_logic/abilities/ability.hpp>

/**
 * Mercenary is a class responsible for representing
 * specialization of entity which is primarily supposed
 * to be controlled by Player.
*/
class Mercenary : public Entity
{
GDCLASS(Mercenary, Entity);

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
        ABILITY_PASSIVE = 0,
        ABILITY_FIRST = 1,
        ABILITY_SECOND = 2,
        ABILITY_THIRD = 3,
        ABILITY_ULTIMATE = 4
    };

    void use_ability(int ability_id, UseContext use_context);
    void use_basic_attack(UseContext use_context);

    void initialize();

    Mercenary();
    ~Mercenary();
};

#endif // MERCENARY_HPP_INCLUDED