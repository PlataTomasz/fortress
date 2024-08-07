#include "ability_caster_component.h"
#include <shared/abilities/test_ability.hpp>
#include <shared/data_holders/action_context.hpp>
#include <shared/helper_macros.h>

#include <shared/abilities/basic_attack.h>
#include <memory.h>

AbilityCasterComponent::AbilityCasterComponent()
{
    DISABLE_IN_EDITOR();
}

void AbilityCasterComponent::_notification(int p_notification)
{

}

void AbilityCasterComponent::use_basic_attack(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(attack);
    attack->use(action_context);
}

void AbilityCasterComponent::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_basic_attack"), &AbilityCasterComponent::get_basic_attack);
    ClassDB::bind_method(D_METHOD("set_basic_attack", "new_basic_attack"), &AbilityCasterComponent::set_basic_attack);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "basic_attack", PROPERTY_HINT_NODE_TYPE, BasicAttack::get_class_static()), "set_basic_attack", "get_basic_attack");

    ClassDB::bind_method(D_METHOD("get_passive_ability"), &AbilityCasterComponent::get_passive_ability);
    ClassDB::bind_method(D_METHOD("set_passive_ability", "new_passive_ability"), &AbilityCasterComponent::set_passive_ability);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "passive_ability", PROPERTY_HINT_NODE_TYPE, Ability::get_class_static()), "set_passive_ability", "get_passive_ability");

    ClassDB::bind_method(D_METHOD("get_first_ability"), &AbilityCasterComponent::get_first_ability);
    ClassDB::bind_method(D_METHOD("set_first_ability", "new_first_ability"), &AbilityCasterComponent::set_first_ability);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "first_ability", PROPERTY_HINT_NODE_TYPE, "Ability"), "set_first_ability", "get_first_ability");

    ClassDB::bind_method(D_METHOD("get_second_ability"), &AbilityCasterComponent::get_second_ability);
    ClassDB::bind_method(D_METHOD("set_second_ability", "new_second_ability"), &AbilityCasterComponent::set_second_ability);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "second_ability", PROPERTY_HINT_NODE_TYPE, "Ability"), "set_second_ability", "get_second_ability");

    ClassDB::bind_method(D_METHOD("get_third_ability"), &AbilityCasterComponent::get_third_ability);
    ClassDB::bind_method(D_METHOD("set_third_ability", "new_third_ability"), &AbilityCasterComponent::set_third_ability);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "third_ability", PROPERTY_HINT_NODE_TYPE, "Ability"), "set_third_ability", "get_third_ability");

    ClassDB::bind_method(D_METHOD("get_ultimate_ability"), &AbilityCasterComponent::get_ultimate_ability);
    ClassDB::bind_method(D_METHOD("set_ultimate_ability", "new_ultimate_ability"), &AbilityCasterComponent::set_ultimate_ability);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ultimate_ability", PROPERTY_HINT_NODE_TYPE, "Ability"), "set_ultimate_ability", "get_ultimate_ability");
}

void AbilityCasterComponent::set_passive_ability(Ability *p_passive_ability) {
    passive_ability = p_passive_ability;
}

Ability *AbilityCasterComponent::get_passive_ability() {
    return passive_ability;
}


Entity *AbilityCasterComponent::get_owning_entity() {
    return Object::cast_to<Entity>(get_parent());
}

void AbilityCasterComponent::set_basic_attack(BasicAttack *p_basic_attack) {
    attack = p_basic_attack;
}

BasicAttack *AbilityCasterComponent::get_basic_attack() {
    return attack;
}

void AbilityCasterComponent::set_first_ability(Ability *p_ability) {
    first_ability = p_ability;
}

Ability *AbilityCasterComponent::get_first_ability() {
    return first_ability;
}

void AbilityCasterComponent::set_second_ability(Ability *p_ability) {
    second_ability = p_ability;
}

Ability *AbilityCasterComponent::get_second_ability() {
    return second_ability;
}

void AbilityCasterComponent::set_third_ability(Ability *p_ability) {
    third_ability = p_ability;
}

Ability *AbilityCasterComponent::get_third_ability() {
    return third_ability;
}


void AbilityCasterComponent::set_ultimate_ability(Ability *p_ability) {
    ultimate_ability = p_ability;
}

Ability *AbilityCasterComponent::get_ultimate_ability() {
    return ultimate_ability;
}

AbilityCasterComponent::~AbilityCasterComponent()
{

}

void AbilityCasterComponent::use_ability(int index, const Ref<ActionContext>& action_context) {
    /*
    ERR_FAIL_COND_V((index > ability_paths.size() || index < 0), void::INTERNAL_ERROR);
    Ability *ability = static_cast<Ability *>(get_node_or_null(ability_paths.get(index).operator NodePath()));
    return ability->use(action_context);
    */
   // TODO: Refactor this - There has to be a better way than this abomination of code
	switch (index) {
		case ABILITY_FIRST: {
            ERR_FAIL_NULL(first_ability);
            return first_ability->use(action_context);
		} break;

        case ABILITY_SECOND: {
            ERR_FAIL_NULL(second_ability);
            return second_ability->use(action_context);
		} break;

        case ABILITY_THIRD: {
            ERR_FAIL_NULL(third_ability);
            return third_ability->use(action_context);
		} break;

        case ABILITY_ULTIMATE: {
            ERR_FAIL_NULL(ultimate_ability);
            return ultimate_ability->use(action_context);
		} break;

		default:
			ERR_FAIL();
	}
}