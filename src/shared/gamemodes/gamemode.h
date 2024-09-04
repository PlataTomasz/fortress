#if !defined(GAMEMODE_INCLUDED)
#define GAMEMODE_INCLUDED

#include <scene/main/node.h>
#include <core/object/class_db.h>
#include <shared/core/player.h>

class Entity;

class Gamemode : public Node {
GDCLASS(Gamemode, Node)
private:
protected:
    void server_rpc_player_lost_game();
public:
    virtual bool is_entity_enemy_of(Entity *first_entity, Entity *second_entity) {
        return false;
    };

#ifdef CLIENT
private:
protected:
public:
#endif

#ifdef SERVER
private:
protected:
public:
    virtual void make_player_lose(const Ref<Player> &player) = 0;
    virtual void make_player_win(const Ref<Player> &player) = 0;
#endif
};

#endif // GAMEMODE_INCLUDED
