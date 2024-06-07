#if !defined(DANCE_WITH_DEATH_STATUS_INCLUDED)
#define DANCE_WITH_DEATH_STATUS_INCLUDED

#include <shared/status_effects/status_effect.hpp>
#include <shared/data_holders/hit_data.h>

class DanceWithDeathStatus : public StatusEffect {
GDCLASS(DanceWithDeathStatus, StatusEffect);
private:
    void _on_self_damage_tick();
    void _on_basic_attack_hit(Entity *hit_entity, const Ref<HitData>& hit_data , Entity *attacker);
protected:
    void _on_apply() override;
    void _on_remove() override;
};

#endif // DANCE_WITH_DEATH_STATUS_INCLUDED
