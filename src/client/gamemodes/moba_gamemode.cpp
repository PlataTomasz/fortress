#include <shared/gamemodes/moba_gamemode.h>

#include <scene/main/multiplayer_peer.h>
#include <shared/core/game_level.h>
#include <client/client.hpp>
#include <scene/main/multiplayer_peer.h>

void MobaGamemode::_ready() {
    _shared_ready();
    Client *client_instance = Client::get_instance();
    ERR_FAIL_NULL(client_instance);
    client_instance->connect("player_connected", callable_mp(this, &MobaGamemode::_on_player_connected));
}

void MobaGamemode::_level_ready() {

}

void MobaGamemode::client_rpc_request_team_data() {
    ERR_FAIL_MSG("Not implemented!");
}

void MobaGamemode::server_rpc_teams_full_data(Dictionary teams_data) {
    ERR_FAIL_NULL(get_gamelevel());
    ERR_FAIL_NULL(first_team);
    ERR_FAIL_NULL(second_team);

    print_line("teams_data received:", teams_data);
    Dictionary first_team_data = teams_data[first_team->get_team_name()];
    Array first_team_entities = first_team_data["entities"];

    Dictionary second_team_data = teams_data[second_team->get_team_name()];
    Array second_team_entities = second_team_data["entities"];

    for(Variant array_entry : first_team_entities) {
        Entity *ent = get_gamelevel()->get_entity(array_entry.operator String());
        ERR_CONTINUE(!ent);
        first_team->add_entity_member(ent);
    }
    
    for(Variant array_entry : second_team_entities) {
        Entity *ent = get_gamelevel()->get_entity(array_entry.operator String());
        ERR_CONTINUE(!ent);
        second_team->add_entity_member(ent);
    }
}

void MobaGamemode::server_rpc_entity_team_join(const String &entity_name, const String &team_name) {
    Ref<Team> team = get_team_by_name(team_name);
    ERR_FAIL_NULL(team);
    ERR_FAIL_NULL(get_gamelevel());

    Entity *ent = get_gamelevel()->get_entity(entity_name);
    ERR_FAIL_NULL(ent);
    team->add_entity_member(ent);
}

void MobaGamemode::server_rpc_entity_team_left(const String &entity_name, const String &team_name) {
    Ref<Team> team = get_team_by_name(team_name);
    ERR_FAIL_NULL(team);
    ERR_FAIL_NULL(get_gamelevel());

    Entity *ent = get_gamelevel()->get_entity(entity_name);
    ERR_FAIL_NULL(ent);
    team->remove_entity_member(ent);
}

void MobaGamemode::_on_entity_joined_team_first(Entity *entity) {

}

void MobaGamemode::_on_entity_joined_team_second(Entity *entity) {

}

void MobaGamemode::_on_entity_left_team_first(Entity *entity) {

}

void MobaGamemode::_on_entity_left_team_second(Entity *entity) {

}

void MobaGamemode::_on_player_connected(const Ref<Player> &player) {
    rpc_id(MultiplayerPeer::TARGET_PEER_SERVER, "client_rpc_request_team_data");
}