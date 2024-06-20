#if !defined(BARBARIAN_BLEEDING_PASSIVE_INCLUDED)
#define BARBARIAN_BLEEDING_PASSIVE_INCLUDED

#include <scene/main/node.h>
#include <shared/entities/components/abilities/ability_caster_component.h>
#include <shared/status_effects/status_effect.hpp>
#include <shared/data_holders/damage_object.hpp>

class Entity;

class BarbarianBleedingPassive : public Ability {
GDCLASS(BarbarianBleedingPassive, Ability);
private:
    //Apply bleeding on-hit to target
    void _on_basic_attack_hit(const Ref<DamageObject>& damage_object, Entity *target);
    void _ready();
protected:
    void _notification(int p_notification);
public:

    void _init();
};

#endif // BARBARIAN_BLEEDING_PASSIVE_INCLUDED
