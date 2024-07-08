#include "entity_name_display.h"

#include <shared/entities/entity.h>

void EntityNameDisplay::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
            _on_entity_change();
		} break;

		default:
			break;
	}
}

void EntityNameDisplay::_on_entity_change() {
    ERR_FAIL_NULL(ent);
    set_text(ent->get_displayed_name());
    ent->connect("displayed_name_changed", callable_mp(this, &EntityNameDisplay::_update_text));
}

void EntityNameDisplay::_update_text(const String& new_text) {
    set_text(new_text);
}

void EntityNameDisplay::_bind_methods() {

    ::ClassDB::bind_method(D_METHOD("get_entity"), &EntityNameDisplay::get_entity);
    ::ClassDB::bind_method(D_METHOD("set_entity"), &EntityNameDisplay::set_entity);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_NODE_TYPE, Entity::get_class_static()), "set_entity", "get_entity");
}