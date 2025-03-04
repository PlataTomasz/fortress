#include "ability_caster_component.h"
#include <shared/abilities/test_ability.hpp>
#include <shared/data_holders/action_context.hpp>
#include <shared/helper_macros.h>

#include <shared/abilities/basic_attack.h>
#include <shared/core/game_level.h>
#include <memory.h>

AbilityCasterComponent::AbilityCasterComponent()
{
    DISABLE_IN_EDITOR();
}

void AbilityCasterComponent::use_basic_attack(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(attack);
    if(attack->can_be_used(action_context)) {
        Dictionary networked_action_data;
        networked_action_data["user_entity_id"] = action_context->get_user() ? action_context->get_user()->get_name() : "0";
        networked_action_data["target_entity_id"] = action_context->get_target_entity() ? action_context->get_target_entity()->get_name() : "0";
        networked_action_data["target_position"] = action_context->get_target_position();
        networked_action_data["use_position"] = action_context->get_use_position();

        rpc("server_rpc_attack_used", networked_action_data);

        attack->use(action_context);
    } else {
        print_error(attack->to_string() + " couldn't be used!");
    }
}

void AbilityCasterComponent::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			ADD_RPC_CONFIG(server_rpc_ability_used, MultiplayerAPI::RPC_MODE_AUTHORITY, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
            ADD_RPC_CONFIG(server_rpc_attack_used, MultiplayerAPI::RPC_MODE_AUTHORITY, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);

            _ready();
		} break;

		default:
			break;
	}
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

    ::ClassDB::bind_method(D_METHOD("server_rpc_ability_used", "ability_index", "networked_action_context"), &AbilityCasterComponent::server_rpc_ability_used);
    ::ClassDB::bind_method(D_METHOD("server_rpc_attack_used", "networked_action_context"), &AbilityCasterComponent::server_rpc_attack_used);

    ADD_SIGNAL(MethodInfo("basic_attack_use_started",
		PropertyInfo(Variant::OBJECT, "basic_attack", PROPERTY_HINT_NODE_TYPE, BasicAttack::get_class_static())
	));

    ADD_SIGNAL(MethodInfo("basic_attack_use_finished",
		PropertyInfo(Variant::OBJECT, "basic_attack", PROPERTY_HINT_NODE_TYPE, BasicAttack::get_class_static())
	));

    ADD_SIGNAL(MethodInfo("ability_use_started",
		PropertyInfo(Variant::OBJECT, "basic_attack", PROPERTY_HINT_NODE_TYPE, Ability::get_class_static())
	));

    ADD_SIGNAL(MethodInfo("ability_use_finished",
		PropertyInfo(Variant::OBJECT, "basic_attack", PROPERTY_HINT_NODE_TYPE, Ability::get_class_static())
	));
}

void AbilityCasterComponent::server_rpc_attack_used(Dictionary networked_action_data) {
    print_line("[INFO] server_rpc_attack_used");
    GameLevel *level = get_owning_entity()->get_gamelevel();

    String user_entity_id = networked_action_data.get("user_entity_id", "0");
    String target_entity_id = networked_action_data.get("target_entity_id", "0");


    Entity *user = level->get_entity(user_entity_id);
    Entity *target = level->get_entity(target_entity_id);

    Ref<ActionContext> local_action_context = memnew(ActionContext(
        user,
        networked_action_data.get("use_position", Vector3(0, 0, 0)),
        networked_action_data.get("target_position", Vector3(0, 0, 0)),
        target
    ));

    
    Ability *ability_to_use = get_basic_attack();
    ERR_FAIL_NULL(ability_to_use);

    ability_to_use->use(local_action_context);
}

void AbilityCasterComponent::server_rpc_ability_used(int which_ability, Dictionary networked_action_data) {
    print_line("[INFO] server_rpc_ability_used");

    GameLevel *level = get_owning_entity()->get_gamelevel();

    String user_entity_id = networked_action_data.get("user_entity_id", "0");
    String target_entity_id = networked_action_data.get("target_entity_id", "0");


    Entity *user = level->get_entity(user_entity_id);
    Entity *target = level->get_entity(target_entity_id);

    Ref<ActionContext> local_action_context = memnew(ActionContext(
        user,
        networked_action_data.get("use_position", Vector3(0, 0, 0)),
        networked_action_data.get("target_position", Vector3(0, 0, 0)),
        target
    ));

    
    Ability *ability_to_use = get_ability_by_index(which_ability);
    ERR_FAIL_NULL(ability_to_use);

    ability_to_use->use(local_action_context);
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

Ability *AbilityCasterComponent::get_ability_by_index(int index) {
    switch (index) {
		case ABILITY_FIRST: {
           return first_ability;
		} break;

        case ABILITY_SECOND: {
            return second_ability;
		} break;

        case ABILITY_THIRD: {
            return third_ability;
		} break;

        case ABILITY_ULTIMATE: {
            return ultimate_ability;
		} break;

		default:
            ERR_FAIL_V_MSG(nullptr, "No such ability index!");
	}
}

AbilityCasterComponent::~AbilityCasterComponent()
{

}

// TODO: #ifdef SERVER
void AbilityCasterComponent::use_ability(int index, const Ref<ActionContext>& action_context) {
    /*
    ERR_FAIL_COND_V((index > ability_paths.size() || index < 0), void::INTERNAL_ERROR);
    Ability *ability = static_cast<Ability *>(get_node_or_null(ability_paths.get(index).operator NodePath()));
    return ability->use(action_context);
    */

    ERR_FAIL_COND(currently_used_ability != nullptr); // We are already using an ability!

    Ability *ability_to_use = get_ability_by_index(index);
    ERR_FAIL_NULL(ability_to_use);

    if(ability_to_use->can_be_used(action_context)) {
        Dictionary networked_action_data;
        networked_action_data["user_entity_id"] = action_context->get_user() ? action_context->get_user()->get_name() : "0";
        networked_action_data["target_entity_id"] = action_context->get_target_entity() ? action_context->get_target_entity()->get_name() : "0";
        networked_action_data["target_position"] = action_context->get_target_position();
        networked_action_data["use_position"] = action_context->get_use_position();

        rpc("server_rpc_ability_used", index, networked_action_data);

        ability_to_use->use(action_context);
    } else {
        print_error(ability_to_use->to_string() + " couldn't be used!");
    }
}

void AbilityCasterComponent::_ready() {
    if(attack) {
        attack->connect("use_started", callable_mp(this, &AbilityCasterComponent::_on_basic_attack_use_started).bind(attack));
        attack->connect("use_finished", callable_mp(this, &AbilityCasterComponent::_on_basic_attack_use_finished).bind(attack));
    }

    for(int i = 1;i<AbilityCasterComponent::ABILITY_MAX;i++) {
        Ability *ability = get_ability_by_index(i);
        ERR_CONTINUE(!ability);

        ability->connect("use_started", callable_mp(this, &AbilityCasterComponent::_on_ability_use_started).bind(ability));
        ability->connect("use_finished", callable_mp(this, &AbilityCasterComponent::_on_ability_use_finished).bind(ability));
    }
}

void AbilityCasterComponent::_on_ability_use_started(Ability *ability) {
    emit_signal("ability_use_started", ability);
}

void AbilityCasterComponent::_on_ability_use_finished(Ability *ability) {
    emit_signal("ability_use_finished", ability);
}

void AbilityCasterComponent::_on_basic_attack_use_started(Ability *basic_attack) {
    emit_signal("basic_attack_use_started", basic_attack);
}

void AbilityCasterComponent::_on_basic_attack_use_finished(Ability *basic_attack) {
    emit_signal("basic_attack_use_finished", basic_attack);
}