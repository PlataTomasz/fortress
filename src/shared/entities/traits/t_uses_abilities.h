#if !defined(T_USES_ABILITIES_INCLUDED)
#define T_USES_ABILITIES_INCLUDED

#include <core/object/class_db.h>

#include "traits.h"

#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/abilities/ability.hpp>

class AbilityCasterComponent;

class TUsesAbilities {
protected:
    AbilityCasterComponent *ability_caster_component = nullptr;
public:
    AbilityCasterComponent *get_ability_caster_component() {
        return ability_caster_component;
    }

    void set_ability_caster_component(AbilityCasterComponent *p_ability_caster_component) {
        ability_caster_component = p_ability_caster_component;
    }

    // TODO: Check if this will cause use_ability method to be overriden in classes, which use that trait
    void use_ability(int index, const Ref<ActionContext>& action_context) {
        ERR_FAIL_NULL(ability_caster_component);
        ability_caster_component->use_ability(index, action_context);
    }

    template<class T>
    static void _bind_trait();
};

template<class T>
void TUsesAbilities::_bind_trait() {
    ::ClassDB::bind_method(D_METHOD("get_ability_caster_component"), method_pointer_fix<T>(&T::get_ability_caster_component));
    ::ClassDB::bind_method(D_METHOD("set_ability_caster_component"), method_pointer_fix<T>(&T::set_ability_caster_component));
    ::ClassDB::add_property(T::get_class_static(), PropertyInfo(Variant::OBJECT, "ability_caster_component", PROPERTY_HINT_NODE_TYPE, "AbilityCasterComponent"), "set_ability_caster_component", "get_ability_caster_component");

    ::ClassDB::bind_method(D_METHOD("use_ability", "p_index", "p_action_context"), method_pointer_fix<T>(&T::use_ability));
}

#endif // T_USES_ABILITIES_INCLUDED
