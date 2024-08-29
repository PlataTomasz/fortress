#if !defined(TEAM_INCLUDED)
#define TEAM_INCLUDED

#include <core/object/object.h>
#include <core/object/class_db.h>
#include <scene/main/node.h>

class Entity;

class Team : public Resource {
GDCLASS(Team, Resource);
private:
    String name = "unnamed";
    // Color of units associated with this team - Without alpha
    Color color = Color(1,1,1);
    List<Entity *> members;
protected:
    static void _bind_methods();
public:
    void set_team_name(const String &name);
    String get_team_name();

    void set_color(const Color &new_color);
    Color get_color();

    bool has_member(Entity *member);
    void remove_member(Entity *new_member);
    void add_member(Entity *new_member);
    void clear_members();
    Vector<Entity *> get_members();

};

#endif // TEAM_INCLUDED
