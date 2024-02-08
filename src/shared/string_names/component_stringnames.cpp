#include "component_stringnames.h"

ComponentStringNames* ComponentStringNames::singleton = nullptr;

ComponentStringNames::ComponentStringNames()
{
    STATUS_EFFECT_VICTIM = StaticCString::create("status_effect_victim_component");
    DAMAGEABLE = StaticCString::create("damageable_component");
}