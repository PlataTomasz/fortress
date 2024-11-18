#include "status_effect_victim_component.h"
#include <core/object/object.h>
#include <scene/resources/packed_scene.h>
#include <shared/core/sh_game.h>
#include <shared/gamemodes/gamemode.h>
#include <shared/entities/components/damage/damageable_component.h>
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

void StatusEffectVictimComponent::_on_child_added(Node *p_child) {
	//FIXME: This is not emmited - Connect it!
	if(Object::cast_to<StatusEffect>(p_child)) {
		emit_signal("status_effect_gained", p_child);
	}
}

void StatusEffectVictimComponent::_on_child_removed(Node *p_child) {
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

		case NOTIFICATION_READY: {
			Entity *ent = get_owning_entity();
			ERR_FAIL_NULL(ent);
			DamageableComponent *damageable = ent->get_damageable_component();
			if(damageable) {
				damageable->connect("death", callable_mp(this, &StatusEffectVictimComponent::_on_death));
			}

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
	if(!can_effect_be_applied(status_effect)) return false;

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

bool StatusEffectVictimComponent::already_has_other_instance(StatusEffect *status_effect) {
	TypedArray<Node> children = get_children();
	for(int i = 0;i<children.size();i++) {
		StatusEffect *already_present_effect = Object::cast_to<StatusEffect>(children[i].operator Object *());
		if(!already_present_effect) continue;

		Variant already_present_meta = already_present_effect->get_meta("identifier");
		Variant status_effect_meta = status_effect->get_meta("identifier");

		if(already_present_effect != Variant() 
			&& already_present_meta == status_effect_meta) {
			return true;
		}
	}
	return false;
}

void StatusEffectVictimComponent::clear() {
	TypedArray<Node> status_effects = get_children();
	for(int i = 0;i<status_effects.size();i++) {
		StatusEffect *status_effect = Object::cast_to<StatusEffect>(status_effects[i].operator Object*());
		if(!status_effect) continue;

		status_effect->queue_free();
	}
}

void StatusEffectVictimComponent::_on_death(const Ref<DamageObject> &damage_object) {
	clear();
}

bool StatusEffectVictimComponent::can_effect_be_applied(StatusEffect *status_effect) {
	ERR_FAIL_NULL_V(status_effect, false);

	SH_Game *game = Realm::get_shared_game();
	ERR_FAIL_NULL_V(game, false);

	Gamemode *gamemode = game->get_gamemode();
	ERR_FAIL_NULL_V(gamemode, false);

	bool is_inflictor_enemy = gamemode->is_entity_enemy_of(status_effect->get_inflictor(), get_owning_entity());

	// TODO: Consider stackable effects
	if(already_has_other_instance(status_effect)) {
		return false;
	}

	if(status_effect->get_type() == StatusEffect::Type::BUFF && !is_inflictor_enemy) {
		return true;
	} else if(status_effect->get_type() == StatusEffect::Type::DEBUFF && is_inflictor_enemy) {
		return true;
	} else if(status_effect->get_type() == StatusEffect::Type::MISC) {
		return true;
	} else {
		return false;
	}
}