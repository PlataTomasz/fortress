#include <shared/gamemodes/moba_gamemode.h>

#include <shared/core/game_level.h>

void MobaGamemode::_ready() {
    _shared_ready();
}

void MobaGamemode::_on_player_connected(const Ref<Player> &player) {
    
}

void MobaGamemode::client_rpc_request_team_data() {
    // Send that data to player
    ERR_FAIL_NULL(get_multiplayer());
    rpc_id(get_multiplayer()->get_remote_sender_id(), "server_rpc_teams_full_data", get_teams_data());
}

void MobaGamemode::server_rpc_teams_full_data(Dictionary teams_data) {
    ERR_FAIL_MSG("Not implemented");
}

void MobaGamemode::server_rpc_entity_team_join(const String &entity_name, const String &team_name) {
    ERR_FAIL_MSG("Not implemented!");
}

void MobaGamemode::server_rpc_entity_team_left(const String &entity_name, const String &team_name) {
    ERR_FAIL_MSG("Not implemented!");
}

void MobaGamemode::_on_entity_joined_team_first(Entity *entity) {
    ERR_FAIL_NULL(entity);
    ERR_FAIL_NULL(first_team);
    rpc("server_rpc_entity_team_join", entity->get_name(), first_team->get_team_name());
}

void MobaGamemode::_on_entity_joined_team_second(Entity *entity) {
    ERR_FAIL_NULL(entity);
    ERR_FAIL_NULL(second_team);
    rpc("server_rpc_entity_team_join", entity->get_name(), second_team->get_team_name());
}

void MobaGamemode::_on_entity_left_team_first(Entity *entity) {
    ERR_FAIL_NULL(entity);
    ERR_FAIL_NULL(first_team);
    rpc("server_rpc_entity_team_left", entity->get_name(), first_team->get_team_name());
}

void MobaGamemode::_on_entity_left_team_second(Entity *entity) {
    ERR_FAIL_NULL(entity);
    ERR_FAIL_NULL(second_team);
    rpc("server_rpc_entity_team_left", entity->get_name(), second_team->get_team_name());
}

void MobaGamemode::_level_ready() {

}