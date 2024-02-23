#include "component_stringnames.h"

ComponentStringNames* ComponentStringNames::singleton = nullptr;

ComponentStringNames::ComponentStringNames()
{
    attribute_component = StaticCString::create("attribute_component");
    status_effect_component = StaticCString::create("status_effect_component");
    damageable_component = StaticCString::create("damageable_component");
    movement_component = StaticCString::create("movement_component");
    damageable_component = StaticCString::create("damageable_component");
}