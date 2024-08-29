#if !defined(GAMEMODE_INCLUDED)
#define GAMEMODE_INCLUDED

#include <scene/main/node.h>
#include <core/object/class_db.h>

class Entity;

class Gamemode : public Node {
GDCLASS(Gamemode, Node)
private:
protected:
public:
    virtual bool is_entity_enemy_of(Entity *first_entity, Entity *second_entity) {
        return false;
    };
};

#endif // GAMEMODE_INCLUDED
