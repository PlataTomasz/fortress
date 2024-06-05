#if !defined(DANCE_WITH_DEATH_STATUS_INCLUDED)
#define DANCE_WITH_DEATH_STATUS_INCLUDED

#include <shared/status_effects/status_effect.hpp>

class DanceWithDeathStatus : public StatusEffect {
GDCLASS(DanceWithDeathStatus, StatusEffect);
protected:
    void _on_apply() override;
    void _on_remove() override;
};

#endif // DANCE_WITH_DEATH_STATUS_INCLUDED
