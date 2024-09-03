#if !defined(MOBA_GAMEMODE_INCLUDED)
#define MOBA_GAMEMODE_INCLUDED

#include "gamemode.h"

#include <shared/core/managers/team.h>

class Entity;



class MobaGamemode : public Gamemode {
GDCLASS(MobaGamemode, Gamemode);
private:
    Ref<Team> first_team;
    Ref<Team> second_team;

    Entity *first_team_nexus = nullptr;
    Entity *second_team_nexus = nullptr;

    void _setup_initial_teams();

    Ref<Team> team_to_asign_next_random;

    void _on_new_entity_enter_level(Entity *entity_that_entered_level);
    void _on_first_nexus_destroyed(Ref<DamageObject> damage_object);
    void _on_second_nexus_destroyed(Ref<DamageObject> damage_object);
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    bool are_entities_same_team(Entity *first_entity, Entity *second_entity);
    virtual bool is_entity_enemy_of(Entity *first_entity, Entity *second_entity) override;
    bool is_entity_in_team(Entity *entity, const Ref<Team>& team);
    Vector<Entity *> get_all_entities_in_team(const Ref<Team>& team);
    Ref<Team> get_team_by_name(const String& team_name);

    Ref<Team> get_first_team();
    void set_first_team(const Ref<Team>& new_first_team);
    Ref<Team> get_second_team();
    void set_second_team(const Ref<Team>& new_second_team);

    Entity *get_first_team_nexus();
    void set_first_team_nexus(Entity *nexus);
    Entity *get_second_team_nexus();
    void set_second_team_nexus(Entity *nexus);

    void asign_to_random_team_balanced(Entity *entity_to_asign);
};

#endif // MOBA_GAMEMODE_INCLUDED
