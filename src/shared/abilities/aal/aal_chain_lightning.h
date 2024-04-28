#if !defined(AAL_CHAIN_LIGHTNING_H_INCLUDED)
#define AAL_CHAIN_LIGHTNING_H_INCLUDED

#include <shared/abilities/active_ability.hpp>

class Area3D;

/**
 * Active: Next basic attack causes lightning to chain from hit target to nearby enemies dealing damage to all nearby units.
*/
class AalChainLightning : public ActiveAbility
{
private:
    //Effect radius
    Area3D* hitbox;
protected:
    void _use(const Ref<ActionContext>& action_context);
public:
    void _ready();
};

#endif // AAL_CHAIN_LIGHTNING_H_INCLUDED
