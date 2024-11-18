#include "turret.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <scene/3d/physics/area_3d.h>
#include <shared/core/game_level.h>
#include <shared/entities/entity.h>
#include <shared/entities/projectile_entity.h>
#include <scene/main/timer.h>
#include <scene/resources/packed_scene.h>
#include <shared/gamemodes/gamemode.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/networking/rpc/rpc_config_builder.h>
#include <shared/networking/rpc/rpc_registerer.h>
#include <shared/collisions/ability_hitbox_helper.h>

#include <shared/gamemodes/moba_gamemode.h>

#ifdef SERVER
void Turret::_initv() {
    attack_cooldown_counter = memnew(Timer);
    attack_cooldown_counter->set_autostart(true);
    attack_cooldown_counter->set_one_shot(true);
    attack_cooldown_counter->connect("timeout", callable_mp(this, &Turret::_on_attack_cooldown_expire));
    add_child(attack_cooldown_counter);
}
#endif

#ifdef CLIENT
void Turret::_initv() {

}
#endif

void Turret::attack_current_target() {
    ERR_FAIL_NULL(current_target);

    GameLevel *game_level = current_target->get_gamelevel();
    ERR_FAIL_NULL(game_level);

    ProjectileEntity *projectile_instance = Object::cast_to<ProjectileEntity>(projectile_template->instantiate());
    ERR_FAIL_NULL(projectile_instance);
    
    // Position needs to be offseted, since it is local
    Vector3 projectile_spawn_position = turret_attack_origin_node ? turret_attack_origin_node->get_global_position() : this->get_position();

    projectile_instance->set_position(projectile_spawn_position);
    projectile_instance->set_target(current_target);
    projectile_instance->set_creator(this);
    projectile_instance->set_name(itos(projectile_instance->get_instance_id()));
    game_level->add_entity(projectile_instance);

    // FIXME: Temporary using hard reference to asign team to projectile instance - Replace with event "when entity is spawned by other entity"
    MobaGamemode *moba_gamemode = Object::cast_to<MobaGamemode>(game_level->get_gamemode());
    ERR_FAIL_NULL(moba_gamemode);

    Ref<Team> team = moba_gamemode->get_team_of_entity(this);
    ERR_FAIL_NULL(team);

    team->add_entity_member(projectile_instance);
    
    EntityAttributesComponent *attributes = get_attributes_component();
    ERR_FAIL_NULL_MSG(attributes, "Missing attributes! Used default value insted!");

    float attack_speed = attributes->get_attack_speed()->get_current();
    float time_between_attacks = 1/attack_speed;

    // Attack speed scaling
    attack_cooldown_counter->start(time_between_attacks);
}

void Turret::_readyv() {
    DamageableComponent *damageable = get_damageable_component();
    if(damageable) {
        damageable->connect("death", callable_mp(this, &Turret::_on_death));
    }

    _setup_recharge_timer();
    _setup_attack_window_timer();

    RPCRegisterer(this, "server_rpc_recharge_started", 
        RPCConfigBuilder()
            .call_local(false)
            .channel(0)
            .rpc_mode(MultiplayerAPI::RPC_MODE_AUTHORITY)
            .transfer_mode(MultiplayerPeer::TRANSFER_MODE_RELIABLE)
            .build()
    );

    RPCRegisterer(this, "server_rpc_recharge_finished", 
        RPCConfigBuilder()
            .call_local(false)
            .channel(0)
            .rpc_mode(MultiplayerAPI::RPC_MODE_AUTHORITY)
            .transfer_mode(MultiplayerPeer::TRANSFER_MODE_RELIABLE)
            .build()
    );
}

Entity *Turret::find_new_target() {
    /*
    1. Search aggro area for potential target by selecting any entity in aggro area
    2. Select other entity in aggro area, if there are no other entities, jump to step 4.
    3. If entity selected in step 2 has higher aggro priotity than entity in step 1, it becomes new potential target
    4. Back to step 2
    5. Return potential target
    */

    AbilityHitboxHelper hitbox_helper(aggro_area);
    return get_closest_entity(hitbox_helper.get_entities_in_area());
}

Entity *Turret::get_closest_entity(const List<Entity *> &potential_closest_entities) {
	ERR_FAIL_COND_V(!(potential_closest_entities.size() > 0), nullptr);

    struct ClosestEntityData {
        Entity *entity = nullptr;
        float squared_distance_to = 0;
    } closest_entity_data;

    // TODO: Create GameCordinates class to store position of entity with possible ignore of y axis, to make easier messing with coordinates

	for (int potential_closest_index = 0; potential_closest_index < potential_closest_entities.size(); potential_closest_index++) {
        Entity *potential_closest_entity = potential_closest_entities.get(potential_closest_index);
        float potential_closest_entity_distance = potential_closest_entity->get_position_2d().distance_squared_to(this->get_position_2d());

		if (potential_closest_entity_distance < closest_entity_data.squared_distance_to && is_entity_valid_target(potential_closest_entity)) {
            closest_entity_data.entity = potential_closest_entity;
            closest_entity_data.squared_distance_to = potential_closest_entity_distance;
		}
	}

	return closest_entity_data.entity;
}

int get_higher_aggro_priority(int first_aggro_priority, int second_aggro_priority) {
    if(first_aggro_priority > second_aggro_priority) {
        return first_aggro_priority;
    } else if(second_aggro_priority >= first_aggro_priority) {
        return second_aggro_priority;
    } else {
        return second_aggro_priority;
    }
}

int Turret::get_aggro_priority_for_entity(Entity *entity) {
    if(entity->has_tag("Mercenary")) {
        return 1;
    } else if(entity->has_tag("Minion")) {
        return 0;
    } else {
        return 1000;
    }
}

void Turret::change_target(Entity *new_target) {
    if(current_target) {
        current_target->get_damageable_component()->disconnect("death", callable_mp(this, &Turret::_on_target_death));
    }
    if(new_target) {
        new_target->get_damageable_component()->connect("death", callable_mp(this, &Turret::_on_target_death));
    }
    current_target = new_target;
}

void Turret::_on_entity_left_aggro_area(Entity *entity_that_left) {
    if(entity_that_left == current_target) {
        _on_target_left_aggro_area();
    }
}

void Turret::_on_death(const Ref<DamageObject> &damage_object) {
    // Prevent firing and change color to indicate
    set_displayed_name("[DESTROYED]");
}

void Turret::_on_target_left_aggro_area() {
    change_target(find_new_target());
}

// Valid target is considered a target that is enemy of turret, has damageable component and is not already dead
bool Turret::is_entity_valid_target(Entity *potential_target) {
    bool is_enemy_of = get_gamelevel()->get_gamemode()->is_entity_enemy_of(this, potential_target);
    DamageableComponent *target_damageable = potential_target->get_damageable_component();

    if(get_gamelevel()->get_gamemode()->is_entity_enemy_of(this, potential_target) 
        && potential_target->get_damageable_component()
        && ((target_damageable && !target_damageable->is_dead()))) {
        return true;
    } else {
        return false;
    }
}

bool Turret::has_target() {
    return (current_target != nullptr);
}

void Turret::_bind_methods() {
    ClassDB::bind_method("server_rpc_recharge_started", &Turret::server_rpc_recharge_started);
    ClassDB::bind_method("server_rpc_recharge_finished", &Turret::server_rpc_recharge_finished);

    ClassDB::bind_method(D_METHOD("get_aggro_area"), &Turret::get_aggro_area);
    ClassDB::bind_method(D_METHOD("set_aggro_area", "aggro_area"), &Turret::set_aggro_area);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aggro_area", PROPERTY_HINT_NODE_TYPE, AdvancedArea3D::get_class_static()), "set_aggro_area", "get_aggro_area");

    ClassDB::bind_method(D_METHOD("get_cooldown_between_attacks"), &Turret::get_cooldown_between_attacks);
    ClassDB::bind_method(D_METHOD("set_cooldown_between_attacks", "cooldown_between_attacks"), &Turret::set_cooldown_between_attacks);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldown_between_attacks"), "set_cooldown_between_attacks", "get_cooldown_between_attacks");

    ClassDB::bind_method(D_METHOD("get_projectile_template"), &Turret::get_projectile_template);
    ClassDB::bind_method(D_METHOD("set_projectile_template", "projectile_template"), &Turret::set_projectile_template);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "projectile_template", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_projectile_template", "get_projectile_template");

    ClassDB::bind_method(D_METHOD("get_turret_attack_origin_node"), &Turret::get_turret_attack_origin_node);
    ClassDB::bind_method(D_METHOD("set_turret_attack_origin_node", "turret_attack_origin_node"), &Turret::set_turret_attack_origin_node);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "turret_attack_origin_node", PROPERTY_HINT_NODE_TYPE, Node3D::get_class_static()), "set_turret_attack_origin_node", "get_turret_attack_origin_node");

    ADD_SIGNAL(MethodInfo("recharge_started"));
    ADD_SIGNAL(MethodInfo("recharge_finished"));
}

void Turret::_on_entity_enter_aggro_area(Entity *entity_that_entered) {
    ERR_FAIL_NULL(get_gamelevel());
    ERR_FAIL_NULL(get_gamelevel()->get_gamemode());

    // Pick a target if don't have one already, then attack if turret was ready to attack
    if(!has_target() && is_entity_valid_target(entity_that_entered)) {
        change_target(entity_that_entered);
        if(current_target && ready_to_attack && can_attack()) {
            attack_current_target();
            ready_to_attack = false;
        }
    }
}

void Turret::set_aggro_area(Area3D *new_aggro_area) {
    aggro_area = new_aggro_area;
    if(aggro_area) {
        aggro_area->connect("area_entered", callable_mp(this, &Turret::_on_aggro_area_entered));
        aggro_area->connect("area_exited", callable_mp(this, &Turret::_on_aggro_area_exited));
    }
}

Area3D *Turret::get_aggro_area() {
    return aggro_area;
}

void Turret::set_cooldown_between_attacks(float new_cooldown) {
    cooldown_between_attacks = new_cooldown;
    DISABLE_IN_EDITOR();
    #ifdef SERVER
    attack_cooldown_counter->set_wait_time(new_cooldown);
    #endif
}

float Turret::get_cooldown_between_attacks() {
    return cooldown_between_attacks;
}

void Turret::set_projectile_template(const Ref<PackedScene>& new_projectile_template) {
    projectile_template = new_projectile_template;
}

Ref<PackedScene> Turret::get_projectile_template() {
    return projectile_template;
}

void Turret::set_turret_attack_origin_node(Node3D *new_origin_node) {
    turret_attack_origin_node = new_origin_node;
}

Node3D *Turret::get_turret_attack_origin_node() {
    return turret_attack_origin_node;
}

void Turret::_setup_recharge_timer() {
    recharge_timer = memnew(Timer);
    recharge_timer->set_one_shot(true);
    recharge_timer->set_wait_time(recharge_time);
    recharge_timer->connect("timeout", callable_mp(this, &Turret::_on_recharge_finished));
    recharge_timer->set_autostart(false);
    add_child(recharge_timer);
}

void Turret::_setup_attack_window_timer() {
    attack_window_timer = memnew(Timer);
    attack_window_timer->set_wait_time(attack_time_window);
    attack_window_timer->set_one_shot(true);
    attack_window_timer->connect("timeout", callable_mp(this, &Turret::_on_attack_window_expire));
    attack_window_timer->set_autostart(true);
    add_child(attack_window_timer);
}

void Turret::_on_attack_cooldown_expire() {
    // Attack target if exists or wait until new target is chosen if not
    if(has_target() && can_attack()) {
        attack_current_target();
    } else {
        ready_to_attack = true;
    }
}

void Turret::_on_target_death(const Ref<DamageObject> &damage_object) {
    change_target(find_new_target());
}

bool Turret::can_attack() {
    DamageableComponent *damageable = get_damageable_component();
    if(damageable) {
        return !recharging && !damageable->is_dead();
    } else {
        return !recharging;
    }
}

float Turret::get_max_recharge_time() {
    ERR_FAIL_NULL_V(recharge_timer, 0);
    return recharge_timer->get_wait_time();
}

float Turret::get_current_recharge_time() {
    ERR_FAIL_NULL_V(recharge_timer, 0);
    return recharge_timer->get_wait_time() - recharge_timer->get_time_left();
}

void Turret::_on_aggro_area_entered(Area3D *area_that_entered) {
    if(area_that_entered->is_in_group("hurtbox")) {
        if(Entity *ent = Object::cast_to<Entity>(area_that_entered->get_parent())) {
            _on_entity_enter_aggro_area(ent);
        }
    }
}

void Turret::_on_aggro_area_exited(Area3D *area_that_exited) {
    if(area_that_exited->is_in_group("hurtbox")) {
        if(Entity *ent = Object::cast_to<Entity>(area_that_exited->get_parent())) {
            _on_entity_left_aggro_area(ent);
        }
    }
}