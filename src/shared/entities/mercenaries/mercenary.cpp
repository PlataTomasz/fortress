#include "mercenary.hpp"
#include <shared/abilities/test_ability.hpp>
#include <shared/helper_macros.h>

#include <shared/entities/components/movement/movement_component.h>

Mercenary::Mercenary()
{

}

Mercenary::~Mercenary()
{
    
}

void Mercenary::_bind_methods() {
    //void (Mercenary::*x)() = &Mercenary::exampleTraitMethod;
    //ClassDB::bind_method(D_METHOD("exampleTraitMethod"), method_pointer_fix<Mercenary>(&Mercenary::exampleTraitMethod));

    TUsesAbilities::_bind_trait<Mercenary>();
    THasAttributes::_bind_trait<Mercenary>();
}

Node *Mercenary::_get_component(const String& component_typename) {
    if (component_typename == ability_caster_component->get_class()) {
        return ability_caster_component;
    } else if (component_typename == attributes_component->get_class()) {
        return attributes_component;
    } else {
        return nullptr;
    }
}