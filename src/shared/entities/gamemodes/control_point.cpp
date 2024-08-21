#include "control_point.h"

#include <scene/3d/physics/area_3d.h>

void ControlPoint::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_PHYSICS_PROCESS:
			_tick();
			break;

		default:
			break;
	}
}

void ControlPoint::_tick() {
    DISABLE_IN_EDITOR();
    double delta = get_physics_process_delta_time();
    //FIXME: Pseudocode showing flow of logic for control point called every frame
    Area3D *area = nullptr;
    TypedArray<Area3D> inside_control_point = area->get_overlapping_areas();
    int mercenary_count[1];
    for (int i = 0;i < inside_control_point.size();i++) {
        //STEPS:
        //Count how many mercenaries there are from each team on control point.
        //  If there are at least 1 mercenary from different teams on the control point, then control_point_progress neither increase nor decrease.
        //  If there are only mercenaries from single team, increase control_point_progress per each mercenary on control point.
        //  If there are no mercenaries on control point, then decrease control_point_progress.
        
    }
}