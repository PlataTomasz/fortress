#include "team.h"

#include <shared/entities/entity.h>

// Team
void Team::set_team_name(const String &p_name) {
    name = p_name;
};

String Team::get_team_name() {
    return name;
};

void Team::set_color(const Color &new_color) {
    color = new_color;
};

Color Team::get_color() {
    return color;
};

Vector<Entity *> Team::get_members() {
    Vector<Entity *> team_members;
    team_members.resize(members.size());
    for(int i = 0;i<members.size();i++) {
        team_members.set(i, members.get(i));
    }
    return team_members;
};

void Team::remove_member(Entity *member) {
    List<Entity *>::Element *elem = members.find(member);

    if(elem) {
        elem->erase();
    }
};

void Team::add_member(Entity *new_member) {
    members.push_back(new_member);
    print_line(new_member, "asigned to team", this);
};

void Team::clear_members() {
    // Emit signal first to notify that anyone who was in that team is now unasigned
    members.clear();
};

bool Team::has_member(Entity *member) {
    List<Entity *>::Element *elem = members.find(member);

    if(elem) {
        return true;
    } else {
        return false;
    }
}

void Team::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_team_name"), &Team::get_team_name);
    ClassDB::bind_method(D_METHOD("set_team_name", "team_name"), &Team::set_team_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "team_name"), "set_team_name", "get_team_name");

    ClassDB::bind_method(D_METHOD("get_color"), &Team::get_color);
    ClassDB::bind_method(D_METHOD("set_color", "color"), &Team::set_color);
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
}