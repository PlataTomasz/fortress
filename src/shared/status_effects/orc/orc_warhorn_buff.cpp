#include "orc_warhorn_buff.h"
 
#include <shared/entities/entity.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>

void OrcWarhornBuff::_on_apply() {
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_attributes_component());

    attack_speed_modifier = memnew(FloatValueModifier);
    attack_speed_modifier->set_value(0.25);
    attack_speed_modifier->set_type(FloatValueModifier::Type::MULTI_MUL);

    get_victim_entity()->get_attributes_component()->get_attack_speed()->add_modifier(attack_speed_modifier);
    print_line("Buff applied on", get_victim_entity(), "- Attack speed is: ", get_victim_entity()->get_attributes_component()->get_attack_speed()->get_current());
}

void OrcWarhornBuff::_on_remove() {
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_attributes_component());

    get_victim_entity()->get_attributes_component()->get_attack_speed()->remove_modifier(attack_speed_modifier);
    print_line("Buff expired on ", get_victim_entity(), "- Attack speed is: ", get_victim_entity()->get_attributes_component()->get_attack_speed()->get_current());
}