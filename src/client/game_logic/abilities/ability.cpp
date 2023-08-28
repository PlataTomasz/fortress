#include <client/game_logic/abilities/ability.hpp>
#include <client/game_logic/abilities/ability_use_chain.hpp>

void Ability::setup_ability_use_chain()
{
    this->ability_use_chain = new CooldownAURCL();
    this->ability_use_chain
        ->set_next(new ResourceCostAURCL());
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

void Ability::set_cost(int new_cost)
{
    this->cost = new_cost;
}

AbilityUseError Ability::use(UseContext& use_context)
{
    AbilityUseError result = this->can_use(use_context);
    if(result == AbilityUseError::SUCCESS)
    {
        //Ability cast 
        this->use_impl(use_context);
    }
    return result;
}

Entity *Ability::get_owner()
{
    return owner.get();
}

void Ability::set_owner(Entity *new_owner)
{
    this->old_owner = this->owner;
    this->owner.reset(new_owner);
    set_owner_callback();
}

void Ability::force_use(UseContext& use_context)
{
    use_impl(use_context);
}

AbilityUseError Ability::can_use(UseContext& use_context)
{
    return ability_use_chain->evaluate({this, use_context});
}

void Ability::tick()
{
    tick_impl();
}

Ability::Ability()
{
    setup_ability_use_chain();
}