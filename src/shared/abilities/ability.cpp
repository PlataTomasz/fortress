#include "ability.hpp"
#include "ability_use_chain.hpp"

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

Error Ability::use(UseContext& use_context)
{
    Error result = this->can_use(use_context);
    if(result == AbilityUseError::SUCCESS)
    {
        //Ability cast 
        this->use_impl(use_context);
    }
    return result;
}

void Ability::tick()
{
    tick_impl();
}

Ability::Ability()
{
    setup_ability_use_chain();
}