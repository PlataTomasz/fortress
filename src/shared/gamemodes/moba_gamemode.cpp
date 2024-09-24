#include "moba_gamemode.h"

#include <shared/entities/entity.h>

#include <shared/core/game_level.h>
#include <shared/core/sh_game.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <scene/main/timer.h>

bool MobaGamemode::is_entity_enemy_of(Entity *first_entity, Entity *second_entity) {
    return !are_entities_same_team(first_entity, second_entity);
}

bool MobaGamemode::are_entities_same_team(Entity *first_entity, Entity *second_entity) {
    if(first_team->has_entity_member(first_entity) && first_team->has_entity_member(second_entity)) {
        return true;
    } else if(second_team->has_entity_member(first_entity) && second_team->has_entity_member(second_entity)) {
        return true;
    } else {
        return false;
    }
}

bool MobaGamemode::is_entity_in_team(Entity *entity, const Ref<Team>& team) {
    return team->has_entity_member(entity);
}

Ref<Team> MobaGamemode::get_team_by_name(const String& team_name) {
    if(first_team->get_name() == team_name) {
        return first_team;
    } else if(second_team->get_name() == team_name) {
        return second_team;
    } else {
        return Ref<Team>();
    }
}

void MobaGamemode::_bind_shared_methods() {
    ClassDB::bind_method(D_METHOD("get_first_team"), &MobaGamemode::get_first_team);
    ClassDB::bind_method(D_METHOD("set_first_team", "first_team"), &MobaGamemode::set_first_team);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "first_team", PROPERTY_HINT_RESOURCE_TYPE, Team::get_class_static()), "set_first_team", "get_first_team");

    ClassDB::bind_method(D_METHOD("get_second_team"), &MobaGamemode::get_second_team);
    ClassDB::bind_method(D_METHOD("set_second_team", "second_team"), &MobaGamemode::set_second_team);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "second_team", PROPERTY_HINT_RESOURCE_TYPE, Team::get_class_static()), "set_second_team", "get_second_team");

    ClassDB::bind_method(D_METHOD("get_first_team_nexus"), &MobaGamemode::get_first_team_nexus);
    ClassDB::bind_method(D_METHOD("set_first_team_nexus", "first_team_nexus"), &MobaGamemode::set_first_team_nexus);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "first_team_nexus", PROPERTY_HINT_NODE_TYPE, Entity::get_class_static()), "set_first_team_nexus", "get_first_team_nexus");

    ClassDB::bind_method(D_METHOD("get_second_team_nexus"), &MobaGamemode::get_second_team_nexus);
    ClassDB::bind_method(D_METHOD("set_second_team_nexus", "second_team_nexus"), &MobaGamemode::set_second_team_nexus);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "second_team_nexus", PROPERTY_HINT_NODE_TYPE, Entity::get_class_static()), "set_second_team_nexus", "get_second_team_nexus");

    ClassDB::bind_method(D_METHOD("server_rpc_defeat"), &MobaGamemode::server_rpc_defeat);
    ClassDB::bind_method(D_METHOD("server_rpc_victory"), &MobaGamemode::server_rpc_victory);

    ADD_SIGNAL(MethodInfo("game_over"));
}

Ref<Team> MobaGamemode::get_first_team() {
    return first_team;
}

void MobaGamemode::set_first_team(const Ref<Team>& new_first_team) {
    first_team = new_first_team;
}

Ref<Team> MobaGamemode::get_second_team() {
    return second_team;
}

void MobaGamemode::set_second_team(const Ref<Team>& new_second_team) {
    second_team = new_second_team;
}

Entity *MobaGamemode::get_first_team_nexus() {
    return first_team_nexus;
}

void MobaGamemode::set_first_team_nexus(Entity *nexus) {
    first_team_nexus = nexus;
}

Entity *MobaGamemode::get_second_team_nexus() {
    return second_team_nexus;
}

void MobaGamemode::set_second_team_nexus(Entity *nexus) {
    second_team_nexus = nexus;
}

void MobaGamemode::respawn_entity(Entity *entity) {
    DamageableComponent *damageable = entity->get_damageable_component();
    ERR_FAIL_NULL_MSG(damageable, "Entity couldn't be respawned!");

    damageable->revive();
}

void MobaGamemode::respawn_entity_at_position(Entity *entity, const Vector3 &respawn_position) {
    DamageableComponent *damageable = entity->get_damageable_component();
    ERR_FAIL_NULL_MSG(damageable, "Entity couldn't be respawned!");

    entity->set_position(respawn_position);
    damageable->revive();
}

void MobaGamemode::_on_death_timer_expire(Entity *entity) {
    Ref<Team> entity_team = get_team_of_entity(entity); 
    Vector3 respawn_position;
    if(entity_team.is_valid()) {
        respawn_position = entity_team->get_respawn_position();
    }

    respawn_entity_at_position(entity, respawn_position);
}

void MobaGamemode::_death_timer_cleanup(Timer *timer) {
    timer->queue_free();
}

void MobaGamemode::_on_entity_death(Entity *entity, const Ref<DamageObject> &damage_object) {
    Timer *death_timer = memnew(Timer);
    death_timer->set_autostart(true);
    death_timer->set_wait_time(death_time);
    death_timer->set_one_shot(true);

    death_timer->connect("timeout", callable_mp(this, &MobaGamemode::_on_death_timer_expire).bind(entity));
    death_timer->connect("timeout", callable_mp(this, &MobaGamemode::_death_timer_cleanup));

    add_child(death_timer);
}

Ref<Team> MobaGamemode::get_team_of_entity(Entity *entity) {
    if(first_team->has_entity_member(entity)) {
        return first_team;
    } else if(second_team->has_entity_member(entity)) {
        return second_team;
    } else {
        return Ref<Team>();
    }
}

void MobaGamemode::_setup_initial_teams() {
    List<Node *> initial_first_team_nodes;
    SceneTree::get_singleton()->get_nodes_in_group("default_team_first", &initial_first_team_nodes);

    List<Node *> initial_second_team_nodes;
    SceneTree::get_singleton()->get_nodes_in_group("default_team_second", &initial_second_team_nodes);

    for(Node *node : initial_first_team_nodes) {
        Entity *ent = Object::cast_to<Entity>(node);
        ERR_CONTINUE(!ent);

        first_team->add_entity_member(ent);
    }

    for(Node *node : initial_second_team_nodes) {
        Entity *ent = Object::cast_to<Entity>(node);
        ERR_CONTINUE(!ent);

        second_team->add_entity_member(ent);
    }
}

Ref<Team> MobaGamemode::asign_player_to_random_team(const Ref<Player>& player) {
    if(team_to_asign_next_player_random.is_valid()) {
        Ref<Team> team_to_add_player = team_to_asign_next_player_random;
        team_to_add_player->add_player_member(player);
        
        if(team_to_asign_next_player_random == first_team) {
            team_to_asign_next_player_random = second_team;
        } else {
            team_to_asign_next_player_random = first_team;
        }

        return team_to_add_player;
    } else {
        first_team->add_player_member(player);
        team_to_asign_next_player_random = second_team;
        return first_team;
    }
}

void MobaGamemode::_on_new_player_join(const Ref<Player>& player) {
    // TODO: Make sure player and controlled entity are in the same team
    ERR_FAIL_NULL(player);
    // FIXME: It fails because controlled_entity is not set at this point!
    Ref<Team> player_team = asign_player_to_random_team(player);
}

void MobaGamemode::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_ENTER_TREE: {
            _enter_tree();
		} break;

        case NOTIFICATION_POSTINITIALIZE: {
            _init();
        } break;

		case NOTIFICATION_READY: {
            _ready();
		} break;

        case NOTIFICATION_PROCESS: {
            #if defined(SERVER)
            
            #endif // SERVER
            
        } break;

		default:
			break;
	}
}

void MobaGamemode::_on_entity_enter_level(Entity *entity_that_entered_level) {
    // If entity was spawned by entity already in team, asign the same team to that entity
    if(entity_that_entered_level->has_meta("spawned_for_player")) {
        Ref<Player> player = entity_that_entered_level->get_meta("spawned_for_player", Ref<Player>());
        
        Ref<Team> player_team = get_player_team(player);
        if(player_team.is_valid()) {
            player_team->add_entity_member(entity_that_entered_level);
            entity_that_entered_level->set_position(player_team->get_respawn_position());
        }
    }
}

Ref<Team> MobaGamemode::get_player_team(const Ref<Player>& player) {
    if(first_team->has_player_member(player)) {
        return first_team;
    } else if(second_team->has_player_member(player)) {
        return second_team;
    } else {
        return Ref<Team>();
    }
}

void MobaGamemode::asign_to_random_team_balanced(Entity *entity_to_asign) {
    if(team_to_asign_next_random.is_valid()) {
        team_to_asign_next_random->add_entity_member(entity_to_asign);
        
        if(team_to_asign_next_random == first_team) {
            team_to_asign_next_random = second_team;
        } else {
            team_to_asign_next_random = first_team;
        }
    } else {
        first_team->add_entity_member(entity_to_asign);
        team_to_asign_next_random = second_team;
    }
}

void MobaGamemode::_register_rpcs() {
    ADD_RPC_CONFIG(
        server_rpc_defeat,
        MultiplayerAPI::RPCMode::RPC_MODE_AUTHORITY,
        MultiplayerPeer::TransferMode::TRANSFER_MODE_RELIABLE,
        0,
        false
    );
    ADD_RPC_CONFIG(
        server_rpc_victory,
        MultiplayerAPI::RPCMode::RPC_MODE_AUTHORITY,
        MultiplayerPeer::TransferMode::TRANSFER_MODE_RELIABLE,
        0,
        false
    );
}

void MobaGamemode::_shared_ready() {
    _register_rpcs();
}

#ifdef CLIENT
void MobaGamemode::_enter_tree() {

}

void MobaGamemode::_init() {
    
}

void MobaGamemode::_ready() {
    _shared_ready();
}

void MobaGamemode::server_rpc_defeat() {
    emit_signal("defeat");
}

void MobaGamemode::server_rpc_victory() {
    emit_signal("victory");
}

void MobaGamemode::_bind_methods() {
    _bind_shared_methods();

    ADD_SIGNAL(MethodInfo("defeat"));
    ADD_SIGNAL(MethodInfo("victory"));
}

#endif

#ifdef SERVER
void MobaGamemode::_ready() {
    _shared_ready();
}

void MobaGamemode::_post_level_load() {
    if(first_team_nexus) {
        DamageableComponent *nexus_damageable = first_team_nexus->get_damageable_component();
        ERR_FAIL_COND_MSG(!nexus_damageable, "Nexus of the first team cannot be damaged! Game is unwinnable for one of the teams!");

        nexus_damageable->connect("death", callable_mp(this, &MobaGamemode::_on_first_nexus_destroyed));
    }

    if(second_team_nexus) {
        DamageableComponent *nexus_damageable = second_team_nexus->get_damageable_component();
        ERR_FAIL_COND_MSG(!nexus_damageable, "Nexus of the second team cannot be damaged! Game is unwinnable for one of the teams!");
        
        nexus_damageable->connect("death", callable_mp(this, &MobaGamemode::_on_second_nexus_destroyed));
    }

    GameLevel *gamelevel = Object::cast_to<GameLevel>(get_parent());
    if(gamelevel) {
        gamelevel->connect("entity_death", callable_mp(this, &MobaGamemode::_on_entity_death));
    }
}

void MobaGamemode::_enter_tree() {
    get_parent()->connect("ready", callable_mp(this, &MobaGamemode::_setup_initial_teams));

    // Connect to GameLevel "entity_added" event
    SH_Game *game = Realm::get_shared_game();
    ERR_FAIL_NULL(game);
    GameLevel *gamelevel = game->get_current_level();
    ERR_FAIL_NULL(gamelevel);
    gamelevel->connect("entity_added", callable_mp(this, &MobaGamemode::_on_entity_enter_level));
    game->connect("post_level_load", callable_mp(this, &MobaGamemode::_post_level_load));

    Server *server = Server::get_instance();

    server->connect("new_player_join", callable_mp(this, &MobaGamemode::_on_new_player_join));
}

void MobaGamemode::_bind_methods() {
    _bind_shared_methods();

}

void MobaGamemode::make_player_lose(const Ref<Player> &player) {
    // TODO: Register this RPC
    rpc_id(player->get_owner_peer_id(), "server_rpc_defeat");
}

void MobaGamemode::make_player_win(const Ref<Player> &player) {
    // TODO: Register this RPC
    rpc_id(player->get_owner_peer_id(), "server_rpc_victory");
}

void MobaGamemode::_init() {
    set_process(true);
    //register_gamemode_server_commands();
}

void MobaGamemode::server_rpc_defeat() {
    // Empty intentionally
}

void MobaGamemode::server_rpc_victory() {
    // Empty intentionally
}

void MobaGamemode::_on_first_nexus_destroyed(const Ref<DamageObject>& damage_object){
    print_line("Game finished and first team won!");
    // Get all players in first team
    Vector<Ref<Player>> first_team_player_members = first_team->get_player_members();
    for(Ref<Player> player : first_team_player_members) {
        make_player_lose(player);
    }

    Vector<Ref<Player>> second_team_player_members = second_team->get_player_members();
    for(Ref<Player> player : second_team_player_members) {
        make_player_win(player);
    }

    emit_signal("game_over");
}

void MobaGamemode::_on_second_nexus_destroyed(const Ref<DamageObject>& damage_object) {
    print_line("Game finished and second team won!");
    // Get all players in first team
    Vector<Ref<Player>> first_team_player_members = first_team->get_player_members();
    for(Ref<Player> player : first_team_player_members) {
        make_player_win(player);
    }

    Vector<Ref<Player>> second_team_player_members = second_team->get_player_members();
    for(Ref<Player> player : second_team_player_members) {
        make_player_lose(player);
    }

    emit_signal("game_over");
}
#endif