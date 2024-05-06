#if !defined(T_USES_ABILITIES_INCLUDED)
#define T_USES_ABILITIES_INCLUDED

#include <core/object/class_db.h>

#include "traits.h"

class AbilityCasterComponent;

class TUsesAbilities {
private:
    AbilityCasterComponent *ability_caster_component = nullptr;
public:
    AbilityCasterComponent *get_ability_caster_component() {
        return ability_caster_component;
    }

    void set_ability_caster_component(AbilityCasterComponent *p_ability_caster_component) {
        ability_caster_component = p_ability_caster_component;
    }


    template<class T>
    static void _bind_trait();
};

template<class T>
void TUsesAbilities::_bind_trait() {
    ::ClassDB::bind_method(D_METHOD("get_ability_caster_component"), method_pointer_fix<T>(&T::get_ability_caster_component));
    ::ClassDB::bind_method(D_METHOD("set_ability_caster_component"), method_pointer_fix<T>(&T::set_ability_caster_component));
    ::ClassDB::add_property(T::get_class_static(), PropertyInfo(Variant::OBJECT, "ability_caster_component", PROPERTY_HINT_NODE_TYPE, "AbilityCasterComponent"), "set_ability_caster_component", "get_ability_caster_component");
}

#endif // T_USES_ABILITIES_INCLUDED
