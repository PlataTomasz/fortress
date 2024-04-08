#include "teams_manager.h"

#include <shared/entities/components/teams/team_member.h>

// TeamData
void TeamData::set_name(const String &p_name) {
    name = p_name;
};

String TeamData::get_name() {
    return name;
};

void TeamData::set_color(const Color &new_color) {
    color = new_color;
};

Color TeamData::get_color() {
    return color;
};

List<Node *> TeamData::get_members() {
    return members;
};

void TeamData::remove_member(Node *member) {
    List<Node *>::Element *elem = members.find(member);

    if(elem) {
        elem->erase();
    }
};

void TeamData::add_member(Node *new_member) {
    members.push_back(new_member);
};

void TeamData::clear_members() {
    // Emit signal first to notify that anyone who was in that team is now unasigned
    members.clear();
};



// TeamsManager
TeamsManager::TeamsManager() {
    singleton = this;
    teams.resize(team_count);
}

TeamsManager *TeamsManager::get_singleton() {
    return singleton;
}

void TeamsManager::change_team(TeamMember *team_member, int new_team_id) {
    emit_signal("team_changed", team_member, new_team_id);
}

void TeamsManager::asign_team(Node *node, int team_id) {
    TeamMember *team_member = memnew(TeamMember);
    team_member->set_current_team(team_id);
}

TeamsManager::~TeamsManager() {

}