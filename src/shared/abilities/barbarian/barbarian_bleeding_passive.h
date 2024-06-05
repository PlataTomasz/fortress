#if !defined(BARBARIAN_BLEEDING_PASSIVE_INCLUDED)
#define BARBARIAN_BLEEDING_PASSIVE_INCLUDED

#include <scene/main/node.h>
#include <shared/entities/components/abilities/ability_caster_component.h>


class Entity;

class BarbarianBleedingPassive : public Node {
private:
    //Apply bleeding on-hit to target
    void _on_basic_attack_hit(Entity *target, AbilityCasterComponent *inflictor, void *caused_by);
public:
    void _init();
};

#endif // BARBARIAN_BLEEDING_PASSIVE_INCLUDED
