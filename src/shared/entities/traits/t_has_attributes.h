#if !defined(T_HAS_ATTRIBUTES_INCLUDED)
#define T_HAS_ATTRIBUTES_INCLUDED

#include <core/object/class_db.h>

#include "traits.h"

#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/abilities/ability.hpp>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>

class THasAttributes {
protected:
    EntityAttributesComponent *attributes_component = nullptr;
public:
    EntityAttributesComponent *get_attributes_component() {
        return attributes_component;
    }

    void set_attributes_component(EntityAttributesComponent *p_attributes_component) {
        attributes_component = p_attributes_component;
    }

    template<class T>
    static void _bind_trait();
};

template<class T>
void THasAttributes::_bind_trait() {
    ::ClassDB::bind_method(D_METHOD("get_attributes_component"), method_pointer_fix<T>(&T::get_attributes_component));
    ::ClassDB::bind_method(D_METHOD("set_attributes_component"), method_pointer_fix<T>(&T::set_attributes_component));
    ::ClassDB::add_property(T::get_class_static(), PropertyInfo(Variant::OBJECT, "attributes_component", PROPERTY_HINT_NODE_TYPE, "EntityAttributesComponent"), "set_attributes_component", "get_attributes_component");
}

#endif // T_HAS_ATTRIBUTES_INCLUDED
