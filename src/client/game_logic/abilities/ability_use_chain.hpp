#if !defined(ABILITY_USE_CHAIN_HPP_INCLUDED)
#define ABILITY_USE_CHAIN_HPP_INCLUDED

#include <client/game_logic/abilities/use_context.hpp>
#include <client/game_logic/abilities/ability.hpp>
#include <shared/resp_chain.hpp>



enum AbilityUseError;

struct AbilityUseData
{
    Ability* ability;
    UseContext use_context;
};

class AbilityUseRCL : public RCL<AbilityUseError, AbilityUseData>
{
public:
    AbilityUseRCL(String identifier) : RCL(identifier)
    {

    }
};

class ResourceCostAURCL : public AbilityUseRCL
{
protected:
    AbilityUseError evaluate_impl(AbilityUseData data) override;
public:
    ResourceCostAURCL(String identifier) : AbilityUseRCL(identifier)
    {
        
    }
};

class CooldownAURCL : public AbilityUseRCL
{
protected:
    AbilityUseError evaluate_impl(AbilityUseData data) override;
public:
    CooldownAURCL(String identifier) : AbilityUseRCL(identifier)
    {
        
    }
};

#endif // ABILITY_USE_CHAIN_HPP_INCLUDED
