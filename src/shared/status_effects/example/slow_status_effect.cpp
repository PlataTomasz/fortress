 #include "slow_status_effect.h"
 
 #include <shared/entities/traits/t_has_attributes.h>

void SlowStatusEffect::_on_apply() {
    THasAttributes *t_has_attributes = dynamic_cast<THasAttributes *>(get_victim_entity());
    ERR_FAIL_NULL(t_has_attributes);
    //if(!t_has_attributes) return;

    EntityAttributesComponent *attributes = t_has_attributes->get_attributes_component();
    ERR_FAIL_NULL(attributes);
    //if(!attributes) return;

    Ref<FloatAttribute> move_speed_atr = attributes->get_movement_speed();
    modifier = Ref(memnew(FloatValueModifier));
    modifier->set_type(FloatValueModifier::Type::MULTI_MUL);
    modifier->set_value(-0.9); // 50% multiplicative reduced

    move_speed_atr->add_modifier(modifier);
    print_line("Slow applied");
    print_line(move_speed_atr->get_current());
}

void SlowStatusEffect::_on_remove() {
    THasAttributes *t_has_attributes = dynamic_cast<THasAttributes *>(get_victim_entity());
    ERR_FAIL_NULL(t_has_attributes);
    //if(!t_has_attributes) return;

    EntityAttributesComponent *attributes = t_has_attributes->get_attributes_component();
    ERR_FAIL_NULL(attributes);
    //if(!attributes) return;

    // Effect ended, remove movement speed penalty
    modifier->expire();
    print_line("Slow expired!");

    Ref<FloatAttribute> move_speed_atr = attributes->get_movement_speed();
    print_line(move_speed_atr->get_current());
}