#include "status_effect.hpp"
#include "../entities/entity.hpp"

StatusEffect::operator String() const
{
    String str = "{\n"
    "   name : %\n"
    "   max_stacks : %\n"
    "   max_duration : %\n"
    "}";

    Array format_data;
    format_data.append(get_name());
    format_data.append(max_stacks);
    format_data.append(max_duration);

    return str.format(format_data, "%");
}