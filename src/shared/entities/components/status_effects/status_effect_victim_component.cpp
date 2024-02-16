#include "status_effect_victim_component.h"
#include <object/ref_counted.h>
#include <scene/resources/packed_scene.h>
#include <shared/status_effects/status_effect_instance.h>

StatusEffectVictimComponent::StatusEffectVictimComponent() {
}
bool StatusEffectVictimComponent::remove_status_effect(StringName status_effect_name) {
	Node *status_effect = get_node_or_null(NodePath(status_effect_name));
	if (status_effect) {
		status_effect->queue_free();
		return true;
	} else {
		return false;
	}
}

bool StatusEffectVictimComponent::has_status_effect(StringName status_effect_name) {
	return get_node_or_null(NodePath(status_effect_name));
}

bool StatusEffectVictimComponent::apply_status_effect(StringName status_effect_name) {
	Ref<PackedScene> status_effect_scene = ResourceLoader::load("res://status_effect/" + String(status_effect_name) + ".tscn");
	Node *instance = status_effect_scene->instantiate();
	add_child(instance);
	return true;
}