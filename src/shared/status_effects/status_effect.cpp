#include "status_effect.hpp"
#include <shared/entities/entity.h>

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

Entity *StatusEffect::get_target() {
    return static_cast<Entity *>(get_parent());
}

void StatusEffect::add_stacks(int stack_count = 1, bool refresh = true) {
    if (current_stacks < max_stacks) {
        current_stacks++;
    }

    if (refresh) {
        current_duration = 0;
    }
}

int StatusEffect::get_current_stacks() {
    return current_stacks;
}