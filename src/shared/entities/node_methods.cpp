#include "node_methods.h"

#include <shared/helpers/object_ptr.h>
#include <shared/entities/components/component.h>
#include <core/variant/variant.h>
#include <type_traits>

template<class T>
T *EntityGlobals::get_component(Node *entity, StringName component_name)
{
    static_assert(std::is_base_of_v<Component, T> == true);
    Variant var = entity->get_meta(component_name);
    return static_cast<T *>(var.operator Object *());
};