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

Vector<Entity *> Team::get_entity_members() {
    Vector<Entity *> team_entity_members;
    team_entity_members.resize(entity_members.size());
    for(int i = 0;i<entity_members.size();i++) {
        team_entity_members.set(i, entity_members.get(i));
    }
    return team_entity_members;
};

void Team::remove_entity_member(Entity *member) {
    List<Entity *>::Element *elem = entity_members.find(member);

    if(elem) {
        elem->erase();
    }
};

void Team::add_entity_member(Entity *new_entity_member) {
    entity_members.push_back(new_entity_member);
    print_line(new_entity_member, "asigned to team", this);
};

void Team::clear_entity_members() {
    // Emit signal first to notify that anyone who was in that team is now unasigned
    entity_members.clear();
};

bool Team::has_entity_member(Entity *member) {
    List<Entity *>::Element *elem = entity_members.find(member);

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

bool Team::has_player_member(const Ref<Player> &player) {
    List<Ref<Player>>::Element *elem = player_members.find(player);

    if(elem) {
        return true;
    } else {
        return false;
    }
}

void Team::remove_player_member(const Ref<Player> &player) {
    List<Ref<Player>>::Element *elem = player_members.find(player);

    if(elem) {
        elem->erase();
    }
}

void Team::add_player_member(const Ref<Player> &player) {
    player_members.push_back(player);
    print_line(player, "asigned to team", this);
}

void Team::clear_player_members() {
    player_members.clear();
}

Vector<Ref<Player>> Team::get_player_members() {
    Vector<Ref<Player>> team_player_members;
    team_player_members.resize(player_members.size());
    for(int i = 0;i<player_members.size();i++) {
        team_player_members.set(i, player_members.get(i));
    }
    return team_player_members;
}