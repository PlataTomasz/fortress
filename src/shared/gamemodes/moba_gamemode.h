#if !defined(MOBA_GAMEMODE_INCLUDED)
#define MOBA_GAMEMODE_INCLUDED

#include "gamemode.h"

#include <shared/core/managers/team.h>
#include <shared/data_holders/damage_object.hpp>
#include <core/variant/dictionary.h>

class Entity;
class Timer;
class GameLevel;

class MobaGamemode : public Gamemode {
GDCLASS(MobaGamemode, Gamemode);
public:
    enum TeamIdentifier {
        NONE,
        FIRST,
        SECOND
    };
private:
    Ref<Team> first_team;
    Ref<Team> second_team;

    Entity *first_team_nexus = nullptr;
    Entity *second_team_nexus = nullptr;

    void _setup_initial_teams();

    Ref<Team> team_to_asign_next_random;
    Ref<Team> team_to_asign_next_player_random;

    float death_time = 15;

    Ref<PackedScene> team_ground_indicator;

    //Players in teams

    void _on_entity_enter_level(Entity *entity_that_entered_level);
    void _on_new_player_join(const Ref<Player>& player);

    void server_rpc_defeat();
    void server_rpc_victory();

    void _init();
    void _ready();
    void _shared_ready();
    void _register_rpcs();
    void _enter_tree();
    void _post_level_load();
    void _on_entity_death(Entity *entity, const Ref<DamageObject> &damage_object);
    void _on_death_timer_expire(Entity *entity);
    void _death_timer_cleanup(Timer *timer);


    void client_rpc_request_team_data();
    void server_rpc_entity_team_join(const String &entity_name, const String &team_name);
    void server_rpc_entity_team_left(const String &entity_name, const String &team_name);
    void server_rpc_teams_full_data(Dictionary teams_data);

    void _on_entity_joined_team_first(Entity *entity);
    void _on_entity_joined_team_second(Entity *entity);
    void _on_entity_left_team_first(Entity *entity);
    void _on_entity_left_team_second(Entity *entity);

    void _level_ready();
    void _on_player_connected(const Ref<Player> &player);
    void _on_entity_join_team(Entity *entity, const Ref<Team> &team);
protected:
    void _notification(int p_notification);
    static void _bind_methods();
    static void _bind_shared_methods();
public:
    virtual Dictionary get_gamemode_data() override;
    virtual void parse_gamemode_data(Dictionary gamemode_data) override;
    Dictionary get_teams_data();
    GameLevel *get_gamelevel();
    void respawn_entity(Entity *entity);
    void respawn_entity_at_position(Entity *entity, const Vector3 &position);
    bool are_entities_same_team(Entity *first_entity, Entity *second_entity);
    virtual bool is_entity_enemy_of(Entity *first_entity, Entity *second_entity) override;
    bool is_entity_in_team(Entity *entity, const Ref<Team>& team);
    Vector<Entity *> get_all_entities_in_team(const Ref<Team>& team);
    Ref<Team> get_team_by_name(const String& team_name);
    Ref<Team> get_team_of_entity(Entity *entity);
    
    Ref<Team> get_player_team(const Ref<Player>& player);

    Ref<Team> get_first_team();
    void set_first_team(const Ref<Team>& new_first_team);
    Ref<Team> get_second_team();
    void set_second_team(const Ref<Team>& new_second_team);

    Entity *get_first_team_nexus();
    void set_first_team_nexus(Entity *nexus);
    Entity *get_second_team_nexus();
    void set_second_team_nexus(Entity *nexus);

    void asign_to_random_team_balanced(Entity *entity_to_asign);
    Ref<Team> asign_player_to_random_team(const Ref<Player>& player);

    void set_team_ground_indicator_vfx(const Ref<PackedScene> &new_team_ground_indicator_vfx);
    Ref<PackedScene> get_team_ground_indicator_vfx();

#ifdef CLIENT
private:
protected:
public:
#endif

#ifdef SERVER
private:
    void _on_first_nexus_destroyed(const Ref<DamageObject> &damage_object);
    void _on_second_nexus_destroyed(const Ref<DamageObject> &damage_object);
protected:
public:
    // Entities are asigned to teams to handle damaging
    virtual void make_player_lose(const Ref<Player> &player) override;
    virtual void make_player_win(const Ref<Player> &player) override;
#endif

};

#endif // MOBA_GAMEMODE_INCLUDED
