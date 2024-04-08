#include "team_member.h"

void TeamMember::_bind_methods() {
    ADD_SIGNAL(MethodInfo("on_team_change", PropertyInfo(Variant::OBJECT, "entity"), PropertyInfo(Variant::INT, "new_team")));

}

void TeamMember::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE:
			
			break;

		default:
			break;
	}
}

bool TeamMember::is_enemy_of(TeamMember *team_member) {
    return this->current_team != team_member->get_current_team();
}

bool TeamMember::is_ally_of(TeamMember *team_member) {
    return this->current_team != team_member->get_current_team();
}

void TeamMember::set_current_team(int new_team) {
    // First ask TeamManager if p_current_team is valid(not greater than current amount of teams)
    ERR_FAIL_COND(!(new_team > TeamsManager::TEAM_UNASIGNED && TeamsManager::get_singleton()->get_team_count() < new_team));

    TeamsManager::get_singleton()->change_team(this, new_team);
    emit_signal("team_changed", new_team);
    current_team = new_team;
}

int TeamMember::get_current_team() {
    return current_team;
}
