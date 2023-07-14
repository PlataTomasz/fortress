#if !defined(FIST_MERCENARY_RIGHT_PUNCH_HPP_INCLUDED)
#define FIST_MERCENARY_RIGHT_PUNCH_HPP_INCLUDED

#include <client/game_logic/abilities/ability.hpp>

class FistMercenaryRightPunchAbility : public Ability
{
    void use_impl(UseContext use_context) override;
public:
    FistMercenaryRightPunchAbility();
};

#endif // FIST_MERCENARY_RIGHT_PUNCH_HPP_INCLUDED
