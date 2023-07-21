#include <client/game_logic/abilities/use_context.hpp>
#include <client/game_logic/abilities/ability_use_chain.hpp>
#include <client/game_logic/abilities/ability.hpp>

AbilityUseError ResourceCostAURCL::evaluate_impl(AbilityUseData data)
{
    UseContext& use_context = data.use_context;
    Entity* user = use_context.get_user();
    Ability* ability = data.ability;

    //TODO: Resource costs



    return AbilityUseError::SUCCESS;
}

AbilityUseError CooldownAURCL::evaluate_impl(AbilityUseData data)
{
    Ability* ability = data.ability;
    if(ability->is_on_cooldown())
    {
        return AbilityUseError::ABILITY_ON_COOLDOWN;
    }
    else
    {
        return AbilityUseError::SUCCESS;
    }
}

AbilityUseError CooldownAURCL::evaluate(AbilityUseData data)
{
    

    return this->evaluate_impl(data);
}