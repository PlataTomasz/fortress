#if !defined(SWORD_MERCENARY_H_INCLUDED)
#define SWORD_MERCENARY_H_INCLUDED

#include <client/entities/mercenaries/mercenary.hpp>

//Abilities
#include <client/game_logic/abilities/sword_mercenary/sword_mercenary_basic_attack.hpp>

class SwordMercenary : public Mercenary
{
GDCLASS(SwordMercenary, Mercenary);

private:

public:
    SwordMercenary()
    {
        //DISABLE_IN_EDITOR();

        basic_attack_ability = memnew(SwordMercenaryBasicAttack);
        
        set_ability(ABILITY_PASSIVE, memnew(TestAbility));
        set_ability(ABILITY_FIRST, memnew(TestAbility));
        set_ability(ABILITY_SECOND, memnew(TestAbility));
        set_ability(ABILITY_THIRD, memnew(TestAbility));
        set_ability(ABILITY_ULTIMATE, memnew(TestAbility));
    };
};

#endif // SWORD_MERCENARY_H_INCLUDED
