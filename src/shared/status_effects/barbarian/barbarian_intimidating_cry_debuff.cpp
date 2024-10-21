#include "barbarian_intimidating_cry_debuff.h"

#include <shared/entities/entity.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>

// TODO: Sync with client properly

void BarbarianIntimidatingCryDebuff::_on_apply() {
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_attributes_component());

    value_modifier = memnew(FloatValueModifier);
    value_modifier->set_value(0.4);
    value_modifier->set_type(FloatValueModifier::Type::MULTI_MUL);

    get_victim_entity()->get_attributes_component()->get_movement_speed()->remove_modifier(value_modifier);
}

void BarbarianIntimidatingCryDebuff::_on_remove() {
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_attributes_component());

    get_victim_entity()->get_attributes_component()->get_movement_speed()->remove_modifier(value_modifier);
}