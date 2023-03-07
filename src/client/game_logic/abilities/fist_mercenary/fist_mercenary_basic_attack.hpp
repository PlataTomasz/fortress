#if !defined(FIST_MERCENARY_BASIC_ATTACK_HPP_INCLUDED)
#define FIST_MERCENARY_BASIC_ATTACK_HPP_INCLUDED

#include <client/game_logic/abilities/basic_attack.hpp>
#include <client/game_logic/abilities/use_context.hpp>

class FistMercenaryBasicAttackAbility : public BasicAttackAbility
{
    void use_impl(UseContext use_context) override;

public:
    void initialize() override;
    
    FistMercenaryBasicAttackAbility(Entity* owner);
};

#endif // FIST_MERCENARY_BASIC_ATTACK_HPP_INCLUDED
