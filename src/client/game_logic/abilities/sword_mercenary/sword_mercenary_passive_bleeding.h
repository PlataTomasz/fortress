#if !defined(SWORD_MERCENARY_PASSIVE_BLEEDING_INCLUDED)
#define SWORD_MERCENARY_PASSIVE_BLEEDING_INCLUDED

#include <client/game_logic/abilities/ability.hpp>

class SwordMercenaryPassive : public Ability
{
private:
    void on_attack_hit();
};

#endif // SWORD_MERCENARY_PASSIVE_BLEEDING_INCLUDED
