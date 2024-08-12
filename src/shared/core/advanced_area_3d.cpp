#include "advanced_area_3d.h"

#include <shared/entities/entity.h>

#include <shared/entities/components/hitbox/hitbox_component.h>

Vector<Entity *> AdvancedArea3D::get_entities_in_area() {
	Vector<Entity *> entities_in_area;

	TypedArray<Area3D> overlapping_areas = get_overlapping_areas();
	for (int i = 0; i < overlapping_areas.size(); i++) {
        Area3D *overlapping_area = (Area3D *)(overlapping_areas[i].operator Object *());
		if (Entity *parent_of_overlapping_area = Object::cast_to<Entity>(overlapping_area->get_parent())) {
			entities_in_area.push_back(parent_of_overlapping_area);
		}
	}

	return entities_in_area;
}

void AdvancedArea3D::_bind_methods() {
    ADD_SIGNAL(MethodInfo("hitbox_entered", PropertyInfo(Variant::OBJECT, "hitbox")));
	ADD_SIGNAL(MethodInfo("hitbox_exited", PropertyInfo(Variant::OBJECT, "hitbox")));
    ADD_SIGNAL(MethodInfo("entity_entered", PropertyInfo(Variant::OBJECT, "entity")));
	ADD_SIGNAL(MethodInfo("entity_exited", PropertyInfo(Variant::OBJECT, "entity")));
}

void AdvancedArea3D::_hitbox_entered(Area3D *p_area) {
	if (HitboxComponent *hitbox = Object::cast_to<HitboxComponent>(p_area)) {
		emit_signal("hitbox_entered", hitbox);
        if(Entity *hitbox_parent = Object::cast_to<Entity>(hitbox->get_parent())) {
            emit_signal("entity_entered", hitbox_parent);
        }
	}
}

void AdvancedArea3D::_hitbox_exited(Area3D *p_area) {
	if (HitboxComponent *hitbox = Object::cast_to<HitboxComponent>(p_area)) {
		emit_signal("hitbox_exited", hitbox);
        if(Entity *hitbox_parent = Object::cast_to<Entity>(hitbox->get_parent())) {
            emit_signal("entity_exited", hitbox_parent);
        }
	}
}

void AdvancedArea3D::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY:
			connect("area_entered", callable_mp(this, &AdvancedArea3D::_hitbox_entered));
			connect("area_exited", callable_mp(this, &AdvancedArea3D::_hitbox_exited));
			break;

		default:
			break;
	}
}