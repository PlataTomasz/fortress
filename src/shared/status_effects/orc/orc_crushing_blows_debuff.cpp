#include "orc_crushing_blows_debuff.h"

#include <shared/core/game_level.h>
#include <shared/entities/entity.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/registries/status_effect_registry.h>

void OrcCrushingBlowsDebuff::_on_apply() {
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_attributes_component());

    defense_modifier = memnew(FloatValueModifier);
    defense_modifier->set_value(-0.25);
    defense_modifier->set_type(FloatValueModifier::Type::MULTI_MUL);

    get_victim_entity()->get_attributes_component()->get_global_defense()->add_modifier(defense_modifier);
}

void OrcCrushingBlowsDebuff::_on_remove() {
    ERR_FAIL_NULL(get_victim_entity());
    ERR_FAIL_NULL(get_victim_entity()->get_attributes_component());

    get_victim_entity()->get_attributes_component()->get_global_defense()->remove_modifier(defense_modifier);
}