#if !defined(FIST_MERCENARY_STRAFE_HPP_INCLUDED)
#define FIST_MERCENARY_STRAFE_HPP_INCLUDED

#include <client/game_logic/abilities/ability.hpp>

/*
Active: Strafe in choosen direction.
*/

class FistMercenaryStrafeAbility: public Ability
{
protected:
    double dash_range = 0.4;

    void use_impl(UseContext use_context) override;
public:
    FistMercenaryStrafeAbility();
};


#endif // FIST_MERCENARY_STRAFE_HPP_INCLUDED

