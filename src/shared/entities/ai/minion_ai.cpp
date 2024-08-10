#include "minion_ai.h"

void MinionAI::_tick() {
    // TODO: I'd need a point-click attack functionality, which would cause an Entity to keep moving toward the entity untill it is in range
}

void MinionAI::start_attacking_entity(Entity *attack_target) {
    // If the same team - ignore; different - attack
    set_current_attack_target(attack_target);
}