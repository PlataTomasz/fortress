#include "status_effect_victim_component.h"
#include <core/object/object.h>
#include <scene/resources/packed_scene.h>

#include <shared/entities/entity.h>

bool StatusEffectVictimComponent::remove_status_effect(StringName status_effect_name) {
	Node *status_effect = get_node_or_null(NodePath(status_effect_name));
	if (status_effect) {
		status_effect->queue_free();
		return true;
	} else {
		return false;
	}
}

void StatusEffectVictimComponent::_on_child_removed(Node *p_child) {
	//FIXME: This is not emmited - Connect it!
	if(Object::cast_to<StatusEffect>(p_child)) {
		emit_signal("status_effect_gained", p_child);
	}
}

void StatusEffectVictimComponent::_on_child_added(Node *p_child) {
	//FIXME: This is not emmited - Connect it!
	if(Object::cast_to<StatusEffect>(p_child)) {
		emit_signal("status_effect_lost", p_child);
	}
}

void StatusEffectVictimComponent::_bind_methods() {
	ADD_SIGNAL(MethodInfo("new_status_gained", PropertyInfo(Variant::OBJECT, "p_status_effect")));
	ADD_SIGNAL(MethodInfo("status_effect_lost", PropertyInfo(Variant::OBJECT, "p_status_effect")));
	ADD_SIGNAL(MethodInfo("status_effect_gained", PropertyInfo(Variant::OBJECT, "p_status_effect")));
}

void StatusEffectVictimComponent::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE: {
			connect("child_exiting_tree", callable_mp(this, &StatusEffectVictimComponent::_on_child_removed));
			connect("child_entered_tree", callable_mp(this, &StatusEffectVictimComponent::_on_child_added));
		} break;

		default:
			break;
	}
}

bool StatusEffectVictimComponent::has_status_effect(StringName status_effect_name) {
	return get_node_or_null(NodePath(status_effect_name));
}

Entity *StatusEffectVictimComponent::get_owning_entity() {
	return Object::cast_to<Entity>(get_parent());
}

bool StatusEffectVictimComponent::apply_status_effect(const StringName &status_effect_name) {
	Ref<PackedScene> status_effect_scene = ResourceLoader::load("res://status_effect/" + String(status_effect_name) + ".tscn");
	Node *instance = status_effect_scene->instantiate();
	add_child(instance);
	return true;
}

bool StatusEffectVictimComponent::apply_status_effect(StatusEffect *status_effect) {
	add_child(status_effect, true);
	return true;
}

List<StatusEffect *> StatusEffectVictimComponent::get_status_effects() {
	List<StatusEffect *> status_effect_list;

	TypedArray<Node> children = get_children();

	for (int i = 0; i < get_child_count(); i++) {
		StatusEffect *child = Object::cast_to<StatusEffect>(children[i].operator Object *());
		if (child) {
			status_effect_list.push_back(child);
		}
	}

	return status_effect_list;
}