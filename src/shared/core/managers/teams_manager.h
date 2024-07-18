#if !defined(TEAMS_MANAGER_INCLUDED)
#define TEAMS_MANAGER_INCLUDED

#include <core/object/object.h>
#include <core/object/class_db.h>
#include <scene/main/node.h>

class TeamData : public Object{
GDCLASS(TeamData, Object);
private:
    String name = "unnamed";
    // Color of units associated with this team - Without alpha
    Color color = Color(1,1,1);
    List<Node *> members;
public:
    void set_name(const String &name);
    String get_name();

    void set_color(const Color &new_color);
    Color get_color();

    void remove_member(Node *new_member);
    void add_member(Node *new_member);
    void clear_members();
    List<Node *> get_members();

};

class TeamMember;

// Global access to team API
class TeamsManager : public Object {
GDCLASS(TeamsManager, Object);
public:
    const static int TEAM_UNASIGNED = 0;
private:
    static TeamsManager *singleton;
    // How many teams there are
    int team_count = 2;
    Vector<TeamData *> teams;
protected:
    static void _bind_methods();
public:
    static TeamsManager *get_singleton();

    // Asigns team to Node, adding TeamMember node as It's child
    void change_team(TeamMember *team_member, int team_id);
    void asign_team(Node *node, int team_id);
    
    int get_team_count();

    TeamsManager();
    ~TeamsManager();
};


#endif // TEAMS_MANAGER_INCLUDED
