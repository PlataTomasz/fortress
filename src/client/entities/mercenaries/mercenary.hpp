#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include "../entity.hpp"
#include "../../game_logic/abilities/ability.hpp"

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
    Ability *skillSet[5];

    static void _bind_methods(){};
public:
    enum AbilitySkillSetIndex
    {
        ABILITY_PASSIVE = 0,
        ABILITY_FIRST = 1,
        ABILITY_SECOND = 2,
        ABILITY_THIRD = 3,
        ABILITY_ULTIMATE = 4
    };

    void castAbility(int abilityId, CastContext castContext);

    Mercenary();
    ~Mercenary();
};

#endif // MERCENARY_HPP_INCLUDED