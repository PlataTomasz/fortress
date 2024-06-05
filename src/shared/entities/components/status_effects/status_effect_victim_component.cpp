#include "status_effect_victim_component.h"
#include <core/object/object.h>
#include <scene/resources/packed_scene.h>

bool StatusEffectVictimComponent::remove_status_effect(StringName status_effect_name) {
	Node *status_effect = get_node_or_null(NodePath(status_effect_name));
	if (status_effect) {
		status_effect->queue_free();
		return true;
	} else {
		return false;
	}
}

void StatusEffectVictimComponent::_bind_methods() {
	ADD_SIGNAL(MethodInfo("new_status_gained", PropertyInfo(Variant::OBJECT, "p_status_effect")));
}

bool StatusEffectVictimComponent::has_status_effect(StringName status_effect_name) {
	return get_node_or_null(NodePath(status_effect_name));
}

bool StatusEffectVictimComponent::apply_status_effect(const StringName &status_effect_name) {
	Ref<PackedScene> status_effect_scene = ResourceLoader::load("res://status_effect/" + String(status_effect_name) + ".tscn");
	Node *instance = status_effect_scene->instantiate();
	add_child(instance);
	return true;
}

bool StatusEffectVictimComponent::apply_status_effect(StatusEffect *status_effect) {
	add_child(status_effect);
	return true;
}