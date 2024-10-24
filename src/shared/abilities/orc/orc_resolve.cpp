#include "orc_resolve.h"

#include <shared/entities/components/damage/damageable_component.h>
#include <scene/main/timer.h>

void OrcResolve::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        {
            Timer *timer = memnew(Timer);
            timer->set_wait_time(1.0);
            timer->set_autostart(true);
            add_child(timer);

            timer->connect("timeout", callable_mp(this, &OrcResolve::_tick));
        }
        break;
    default:
        break;
    }
}