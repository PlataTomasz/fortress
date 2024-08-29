#include "moba_gamemode.h"

#include <shared/entities/entity.h>

#include <shared/core/game_level.h>
#include <shared/core/sh_game.h>

bool MobaGamemode::is_entity_enemy_of(Entity *first_entity, Entity *second_entity) {
    return !are_entities_same_team(first_entity, second_entity);
}

bool MobaGamemode::are_entities_same_team(Entity *first_entity, Entity *second_entity) {
    if(first_team->has_member(first_entity) && first_team->has_member(second_entity)) {
        return true;
    } else if(second_team->has_member(first_entity) && second_team->has_member(second_entity)) {
        return true;
    } else {
        return false;
    }
}

bool MobaGamemode::is_entity_in_team(Entity *entity, const Ref<Team>& team) {
    return team->has_member(entity);
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

void MobaGamemode::_bind_methods() {
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

void MobaGamemode::_setup_initial_teams() {
    List<Node *> initial_first_team_nodes;
    SceneTree::get_singleton()->get_nodes_in_group("default_team_first", &initial_first_team_nodes);

    List<Node *> initial_second_team_nodes;
    SceneTree::get_singleton()->get_nodes_in_group("default_team_second", &initial_second_team_nodes);

    for(Node *node : initial_first_team_nodes) {
        Entity *ent = Object::cast_to<Entity>(node);
        ERR_CONTINUE(!ent);

        first_team->add_member(ent);
    }

    for(Node *node : initial_second_team_nodes) {
        Entity *ent = Object::cast_to<Entity>(node);
        ERR_CONTINUE(!ent);

        second_team->add_member(ent);
    }
}

void MobaGamemode::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_ENTER_TREE: {
            get_parent()->connect("ready", callable_mp(this, &MobaGamemode::_setup_initial_teams));
            
            // Connect to GameLevel "entity_added" event

            SH_Game *game = Realm::get_shared_game();
            ERR_FAIL_NULL(game);
            GameLevel *gamelevel = game->get_current_level();
            ERR_FAIL_NULL(gamelevel);
            gamelevel->connect("entity_added", callable_mp(this, &MobaGamemode::_on_new_entity_enter_level));
		} break;

		default:
			break;
	}
}

void MobaGamemode::_on_new_entity_enter_level(Entity *entity_that_entered_level) {
    if(entity_that_entered_level->get_meta("spawned_by_player_connect", false)) {
        asign_to_random_team_balanced(entity_that_entered_level);
    }
}

void MobaGamemode::asign_to_random_team_balanced(Entity *entity_to_asign) {
    if(team_to_asign_next_random.is_valid()) {
        team_to_asign_next_random->add_member(entity_to_asign);
        
        if(team_to_asign_next_random == first_team) {
            team_to_asign_next_random = second_team;
        } else {
            team_to_asign_next_random = first_team;
        }
    } else {
        first_team->add_member(entity_to_asign);
        team_to_asign_next_random = second_team;
    }
}