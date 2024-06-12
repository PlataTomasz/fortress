#if !defined(DANCE_WITH_DEATH_STATUS_INCLUDED)
#define DANCE_WITH_DEATH_STATUS_INCLUDED

#include <shared/status_effects/status_effect.hpp>
#include <shared/data_holders/hit_data.h>
#include <shared/data_holders/damage_object.hpp>

class DanceWithDeathStatus : public StatusEffect {
GDCLASS(DanceWithDeathStatus, StatusEffect);
private:
    void _on_self_damage_tick();
    void _on_basic_attack_damage_dealt(const Ref<DamageObject> damage_object, Entity *target);
protected:
    void _on_apply() override;
    void _on_remove() override;
};

#endif // DANCE_WITH_DEATH_STATUS_INCLUDED
