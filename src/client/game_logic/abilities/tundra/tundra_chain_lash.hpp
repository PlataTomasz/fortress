#if !defined(TUNDRA_CHAIN_LASH_HPP)
#define TUNDRA_CHAIN_LASH_HPP

#include "../ability.hpp"

class TundraChainLashAbility : public Ability
{
    virtual void initialize(){};
    virtual void onCast();
    virtual void onTick();
    virtual void onCooldownChange(){};

    virtual void use(UseContext use_context);

    ~TundraChainLashAbility()
    {
        
    }
};

#endif // TUNDRA_CHAIN_LASH_HPP
