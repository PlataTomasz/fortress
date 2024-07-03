#include "entity_health_bar.h"

void EntityHealthBar::_bind_methods() {
	::ClassDB::bind_method(D_METHOD("get_value_indicator"), &EntityHealthBar::get_value_indicator);
    ::ClassDB::bind_method(D_METHOD("set_value_indicator"), &EntityHealthBar::set_value_indicator);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "value_indicator", PROPERTY_HINT_NODE_TYPE, Label::get_class_static()), "set_value_indicator", "get_value_indicator");

    ::ClassDB::bind_method(D_METHOD("get_entity"), &EntityHealthBar::get_entity);
    ::ClassDB::bind_method(D_METHOD("set_entity"), &EntityHealthBar::set_entity);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_NODE_TYPE, Entity::get_class_static()), "set_entity", "get_entity");
}

void EntityHealthBar::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE: {
			_value_indicator = memnew(Label);
			_value_indicator->set_horizontal_alignment(HorizontalAlignment::HORIZONTAL_ALIGNMENT_CENTER);
			_value_indicator->set_anchors_preset(LayoutPreset::PRESET_FULL_RECT);
			add_child(_value_indicator, false, Node::INTERNAL_MODE_BACK);
		} break;

		case NOTIFICATION_READY:
		{
			_update_healthbar();
		} break;
		
		default:
			break;
	}
}