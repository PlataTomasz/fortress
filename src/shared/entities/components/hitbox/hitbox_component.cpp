#include "hitbox_component.h"

#include <shared/helper_macros.h>

#include <scene/3d/area_3d.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/cylinder_shape_3d.h>

#include <shared/entities/entity.h>

void HitboxComponent::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			_ready();
		} break;

		default:
			break;
	}
}

Entity *HitboxComponent::get_owning_entity() {
    return Object::cast_to<Entity>(get_parent());
}

void HitboxComponent::_bind_methods() {
	ADD_SIGNAL(MethodInfo("hitbox_entered", PropertyInfo(Variant::OBJECT, "hitbox")));
	ADD_SIGNAL(MethodInfo("hitbox_exited", PropertyInfo(Variant::OBJECT, "hitbox")));
}

void HitboxComponent::_ready() {
	connect("area_entered", callable_mp(this, &HitboxComponent::_on_hitbox_entered));
	connect("area_exited", callable_mp(this, &HitboxComponent::_on_hitbox_exited));
}

void HitboxComponent::_on_hitbox_entered(Area3D *p_area) {
	if (HitboxComponent *hitbox = Object::cast_to<HitboxComponent>(p_area)) {
		emit_signal("hitbox_entered", hitbox);
	}
}

void HitboxComponent::_on_hitbox_exited(Area3D *p_area) {
	if (HitboxComponent *hitbox = Object::cast_to<HitboxComponent>(p_area)) {
		emit_signal("hitbox_exited", hitbox);
	}
}

void _notification(int p_notification);

List<HitboxComponent *> HitboxComponent::get_overlapping_hitboxes() {
	List<HitboxComponent *> hitboxes;

	TypedArray<Area3D> areas = get_overlapping_areas();
	for (int i = 0; i < areas.size(); i++) {
		HitboxComponent *hitbox = Object::cast_to<HitboxComponent>(areas[i].operator Object *());
		if (hitbox) {
			hitboxes.push_back(hitbox);
		}
	}

	return hitboxes;
}