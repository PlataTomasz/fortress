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

    _bind_t_uses_abilities<Mercenary>();
}