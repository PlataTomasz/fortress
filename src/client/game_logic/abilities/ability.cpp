#include <client/game_logic/abilities/ability.hpp>
#include <client/game_logic/abilities/ability_use_chain.hpp>

void Ability::setup_ability_use_chain()
{
    this->ability_use_chain = new CooldownAURCL("cooldown");
    this->ability_use_chain
        ->set_next(new ResourceCostAURCL("cost"));
}

int Ability::get_current_cooldown()
{
    return this->curr_cooldown;
}

int Ability::get_max_cooldown()
{
    return this->max_cooldown;
}

bool Ability::is_on_cooldown()
{
    return this->curr_cooldown > 0;
}

int Ability::get_cost()
{
    return this->cost;
}

void Ability::set_cost(int cost)
{
    this->cost = cost;
}

AbilityUseError Ability::use(UseContext use_context)
{
    AbilityUseError result = this->can_use(use_context);
    if(result == 0)
    {
        //Ability cast 
        this->use_impl(use_context);
    }
    return result;
}

void Ability::force_use(UseContext use_context)
{
    use_impl(use_context);
}

AbilityUseError Ability::can_use(UseContext use_context)
{
    return ability_use_chain->evaluate({this, use_context});
}

Ability::Ability()
{
    setup_ability_use_chain();
}