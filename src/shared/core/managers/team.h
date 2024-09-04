#if !defined(TEAM_INCLUDED)
#define TEAM_INCLUDED

#include <core/object/object.h>
#include <core/object/class_db.h>
#include <scene/main/node.h>

#include <shared/core/player.h>

class Entity;

class Team : public Resource {
GDCLASS(Team, Resource);
private:
    String name = "unnamed";
    // Color of units associated with this team - Without alpha
    Color color = Color(1,1,1);
    List<Entity *> entity_members;
    List<Ref<Player>> player_members;
protected:
    static void _bind_methods();
public:
    void set_team_name(const String &name);
    String get_team_name();

    void set_color(const Color &new_color);
    Color get_color();

    bool has_entity_member(Entity *member);
    void remove_entity_member(Entity *new_member);
    void add_entity_member(Entity *new_member);
    void clear_entity_members();
    Vector<Entity *> get_entity_members();

    bool has_player_member(const Ref<Player> &player);
    void remove_player_member(const Ref<Player> &player);
    void add_player_member(const Ref<Player> &player);
    void clear_player_members();
    Vector<Ref<Player>> get_player_members();
};

#endif // TEAM_INCLUDED
