#if !defined(TEAM_CONTROLER_INCLUDED)
#define TEAM_CONTROLER_INCLUDED

#include <scene/main/node.h>

class TeamControler : public Node {
private:
    // Stores all nodes that have a team asigned
    Vector<Vector<Node *>> teamed_nodes;

public:
    bool is_enemy_of(Node *first, Node *second);
    bool is_ally_of(Node *first, Node *second);

    bool is_member_of_team(Node *node, int team_id);
    // By default nodes are considered to be in TEAM_NONE(-1)
    bool change_team(Node *node, int team_id);

    TeamControler();
};

#endif // TEAM_CONTROLER_INCLUDED
