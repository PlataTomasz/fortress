#if !defined(T_DAMAGEABLE_INCLUDED)
#define T_DAMAGEABLE_INCLUDED

#include "traits.h"

#include <shared/entities/components/damage/damageable_component.h>

class TDamageable {
private:
    DamageableComponent *damageable_component = nullptr;
public:
    void set_damageable_component(DamageableComponent *p_damageable_component) {
        damageable_component = p_damageable_component;
    }

    DamageableComponent *get_damageable_component() {
        return damageable_component;
    }

    void heal(float value) {
        ERR_FAIL_NULL(damageable_component);
        damageable_component->heal(value);
    }

    template<class T>
    static void _bind_trait() {
        ::ClassDB::bind_method(D_METHOD("get_damageable_component"), method_pointer_fix<T>(&T::get_damageable_component));
        ::ClassDB::bind_method(D_METHOD("set_damageable_component"), method_pointer_fix<T>(&T::set_damageable_component));
        ::ClassDB::add_property(T::get_class_static(), PropertyInfo(Variant::OBJECT, "damageable_component", PROPERTY_HINT_NODE_TYPE, "AbilityCasterComponent"), "set_damageable_component", "get_damageable_component");

        ::ClassDB::bind_method(D_METHOD("heal", "p_value"), method_pointer_fix<T>(&T::heal));
    }
};

#endif // T_DAMAGEABLE_INCLUDED
