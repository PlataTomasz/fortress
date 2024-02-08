#if !defined(SWORD_MERCENARY_BASIC_ATTACK_HPP_INCLUDED)
#define SWORD_MERCENARY_BASIC_ATTACK_HPP_INCLUDED

#include "../basic_attack.hpp"

class SwordMercenaryBasicAttack : public BasicAttackAbility
{
protected:
    void use_impl(UseContext& use_context) override;
};

#endif // SWORD_MERCENARY_BASIC_ATTACK_HPP_INCLUDED
