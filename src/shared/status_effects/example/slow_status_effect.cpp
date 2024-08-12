#include "slow_status_effect.h"

#include <shared/entities/entity.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>

void SlowStatusEffect::_on_apply() {
    ERR_FAIL_NULL(get_victim_entity());

    EntityAttributesComponent *attributes = get_victim_entity()->get_attributes_component();
    ERR_FAIL_NULL(attributes);
    
    Ref<FloatAttribute> move_speed_atr = attributes->get_movement_speed();
    modifier = Ref(memnew(FloatValueModifier));
    modifier->set_type(FloatValueModifier::Type::MULTI_MUL);
    modifier->set_value(-0.9); // 50% multiplicative reduced

    move_speed_atr->add_modifier(modifier);
    print_line("Slow applied");
    print_line(move_speed_atr->get_current());
}

void SlowStatusEffect::_on_remove() {
    ERR_FAIL_NULL(get_victim_entity());

    EntityAttributesComponent *attributes = get_victim_entity()->get_attributes_component();
    ERR_FAIL_NULL(attributes);

    // Effect ended, remove movement speed penalty
    modifier->expire();
    print_line("Slow expired!");

    Ref<FloatAttribute> move_speed_atr = attributes->get_movement_speed();
    print_line(move_speed_atr->get_current());
}