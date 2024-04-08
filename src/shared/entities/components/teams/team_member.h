#if !defined(TEAM_MEMBER_INLCUDED)
#define TEAM_MEMBER_INLCUDED

#include <scene/main/node.h>
#include <shared/core/managers/teams_manager.h>

// Stores information about which team does the parent Node belongs to. If TeamMember node is missing, then Node is in no team
class TeamMember : public Node {
private:
    // ID of current team
    int current_team = TeamsManager::TEAM_UNASIGNED;

    void _notification(int p_notification);
protected:
    static void _bind_methods();
public:
    // Checks wheter this TeamMember instance is in different team than passed node
    bool is_enemy_of(TeamMember *node);
    // Checks wheter this TeamMember instance is in the same team as passed node
    bool is_ally_of(TeamMember *node);

    // Getters/Setters
    void set_current_team(int p_current_team);
    int get_current_team();
};

#endif // TEAM_MEMBER_INLCUDED
