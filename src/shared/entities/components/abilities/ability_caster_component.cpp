#include "ability_caster_component.h"
#include <shared/abilities/test_ability.hpp>
#include <shared/data_holders/action_context.hpp>
#include <shared/helper_macros.h>

#include <memory.h>

AbilityCasterComponent::AbilityCasterComponent()
{
    DISABLE_IN_EDITOR();
}

void AbilityCasterComponent::_notification(int p_notification)
{

}

void AbilityCasterComponent::_bind_methods()
{
    // FIXME: For some reason this property is displayed empty even though it has value at runtime
    ClassDB::bind_method(D_METHOD("get_ability_paths"), &AbilityCasterComponent::get_ability_paths);
    ClassDB::bind_method(D_METHOD("set_ability_paths", "new_ability_paths"), &AbilityCasterComponent::set_ability_paths);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "abilities", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_NODE_TYPE, "Ability")), "set_ability_paths", "get_ability_paths");
}

AbilityCasterComponent::~AbilityCasterComponent()
{

}

Array AbilityCasterComponent::get_ability_paths() {
    return ability_paths;
}

void AbilityCasterComponent::set_ability_paths(const Array &new_abilities) {
    ability_paths = new_abilities;
}


Ability::AbilityUseError AbilityCasterComponent::use_ability(int index, const Ref<ActionContext>& action_context) {
    ERR_FAIL_COND_V((index <= ability_paths.size() || index < 0), Ability::AbilityUseError::INTERNAL_ERROR);
    Ability *ability = static_cast<Ability *>(ability_paths.get(index).operator Object *());
    return ability->use(action_context);
}