#include "status_effect.hpp"
#include "../entities/entity.hpp"



Entity *StatusEffect::get_target()
{
    return target;
}

void StatusEffect::set_target(Entity* new_target)
{
    //Disallow change of owner if it was already set
    /*
    if(this->target == nullptr)
    {
        this->target = target;
    }
    */
   this->target = new_target;
}

void StatusEffect::add_stacks(int stack_count)
{
    this->curr_stacks = this->curr_stacks + stack_count;
    //Renew status effect
    curr_duration = 0;
}

void StatusEffect::on_process_frame_impl()
{
    on_process_frame();
    if(curr_duration >= max_duration)
    {
        //Effect duration ended - remove it
        target->remove_status_effect(name);
    }
    else
    {
        curr_duration--;
    }
}

int StatusEffect::get_current_stacks()
{
    return curr_stacks;
}

StatusEffect::operator String() const
{
    String str = "{\n"
    "   name : %\n"
    "   friendlyName : %\n"
    "   tooltip : %\n"
    "   maxStacks : %\n"
    "   currDuration : %\n"
    "   maxDuration : %\n"
    "}";

    Array format_data;
    format_data.append(name);
    format_data.append(friendly_name);
    format_data.append(tooltip);
    format_data.append(max_stacks);
    format_data.append(curr_duration);
    format_data.append(max_duration);

    return str.format(format_data, "%");
}