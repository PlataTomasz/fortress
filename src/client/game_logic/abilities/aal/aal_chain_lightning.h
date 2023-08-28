#if !defined(AAL_CHAIN_LIGHTNING_H_INCLUDED)
#define AAL_CHAIN_LIGHTNING_H_INCLUDED

#include <client/game_logic/abilities/active_ability.hpp>

/**
 * Active: Next basic attack causes lightning to chain from hit target to nearby enemies dealing damage to all nearby units.
*/
class AalChainLightning : public ActiveAbility
{
private:
    //Effect radius
    Area3D* hitbox;
protected:
public:
    void use_impl(UseContext& use_context) override;
    void ready_impl() override;
};

#endif // AAL_CHAIN_LIGHTNING_H_INCLUDED
