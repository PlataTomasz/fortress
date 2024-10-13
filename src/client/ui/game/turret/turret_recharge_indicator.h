#if !defined(TURRET_RECHARGE_INDICATOR_INCLUDED)
#define TURRET_RECHARGE_INDICATOR_INCLUDED

#include <scene/gui/flow_container.h>
#include <scene/gui/texture_rect.h>
#include <scene/gui/progress_bar.h>

class Turret;

class TurretRechargeIndicator : public HFlowContainer {
GDCLASS(TurretRechargeIndicator, HFlowContainer);
private:
    Turret *turret = nullptr;
    Range *progress_bar = nullptr;

    void _on_recharge_started();
    void _on_recharge_finished();

    void _draw();
    void _ready();
protected:
    static void _bind_methods();
    void _notification(int p_notification);
public:
    void set_turret(Turret *new_turret);
    Turret *get_turret();
    void set_progress_bar(Range *new_progress_bar);
    Range *get_progress_bar();
};

#endif // TURRET_RECHARGE_INDICATOR_INCLUDED
