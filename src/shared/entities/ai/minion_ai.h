#if !defined(MINION_AI_INCLUDED)
#define MINION_AI_INCLUDED

#include "entity_ai.h"
#include <scene/3d/path_3d.h>

class Entity;

class MinionAI : public EntityAI {
private:
    Path3D *path_to_target = nullptr;

    Entity *current_attack_target = nullptr;

    void _init() {
        /*
        1. Move along path
        2. If Enemy is ecountered follow that enemy
            - If you've strayed from your path too much, return to the point you've left your path
            - If enemy is in attack range, attack him
        */


    }

    void _tick();
    void start_attacking_entity(Entity *attack_target);
public:
    void set_current_attack_target(Entity *new_target) {
        current_attack_target = new_target;
    }

    Entity *get_current_attack_target() {
        return current_attack_target;
    }
};

#endif // MINION_AI_INCLUDED
