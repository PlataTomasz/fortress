#include "ability.hpp"

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

Ability::AbilityUseError Ability::use(const Ref<UseContext>& use_context)
{
    Ability::AbilityUseError result = VariantCaster<AbilityUseError>::cast(call("use_check", use_context));
    if(result == Ability::AbilityUseError::SUCCESS)
    {
        //Ability cast 
        call("_use", use_context);
    }
    return result;
}

void Ability::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			break;

		default:
			break;
	}
};

Entity *Ability::get_owner()
{
    return static_cast<Entity *>(get_parent());
}

void Ability::force_use(const Ref<UseContext>& use_context)
{
    
}

Ability::AbilityUseError Ability::use_check(const Ref<UseContext>& use_context)
{
    return Ability::AbilityUseError::SUCCESS;
}

void Ability::tick()
{
    tick_impl();
}

Ability::Ability()
{
    
}

void Ability::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_use", "use_context"), &Ability::_use);
    ClassDB::bind_method(D_METHOD("use", "use_context"), &Ability::use);
    ClassDB::bind_method(D_METHOD("use_check", "use_context"), &Ability::use_check);
}