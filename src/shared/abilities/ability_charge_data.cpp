#include "ability_charge_data.h"
#include <scene/main/timer.h>

void AbilityChargeData::initialize()
{
    SceneTree::get_singleton()->create_timer(0.5);
}