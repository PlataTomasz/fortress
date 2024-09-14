#include "visual_component_3d.h"

#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/3d/primitive_meshes.h>
#include <shared/entities/entity.h>
#include <shared/entities/components/movement/movement_component.h>
#include <shared/entities/components/damage/damageable_component.h>

void VisualComponent3D::_notification(int p_notification) {
	DISABLE_IN_EDITOR();
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			break;
		case NOTIFICATION_READY: {
			Entity* ent = get_owning_entity();
			ERR_FAIL_NULL(ent);

			MovementComponent *movement_component = ent->get_movement_component();
			if(movement_component) {
				movement_component->connect("movement_started", callable_mp(this, &VisualComponent3D::_on_movement_start));
				movement_component->connect("movement_finish", callable_mp(this, &VisualComponent3D::_on_movement_finish));
			} else {
				print_error("Movement component is null!");
			}

			ERR_FAIL_NULL(animation_player);
			animation_player->connect("animation_finished", callable_mp(this, &VisualComponent3D::_on_animation_finish));
		}
		break;

		default:
			break;
	}
}

void VisualComponent3D::_on_movement_start() {
	play_walk_animation();
}

void VisualComponent3D::_on_movement_finish() {
	play_idle_animation();
}

Entity *VisualComponent3D::get_owning_entity() {
    return Object::cast_to<Entity>(get_parent());
}

void VisualComponent3D::switch_to_idle_animation() {
	ERR_FAIL_NULL(animation_player);

	animation_player->set_next_from_any_library("idle");
	animation_state = AnimationState::IDLE;
}

void VisualComponent3D::switch_to_walk_animation() {
	ERR_FAIL_NULL(animation_player);

	animation_player->set_next_from_any_library("Walk002");
	animation_state = AnimationState::WALK;
}

void VisualComponent3D::_on_animation_finish(const String& animation_name) {
	// TODO: Reimplement with state pattern
	ERR_FAIL_NULL(animation_player);

	// This also triggers if animation is changed
	if((animation_player->get_current_animation_length() - animation_player->get_current_animation_position()) > 0) return; //fix

	Entity *ent = get_owning_entity();
	ERR_FAIL_NULL(ent);

	MovementComponent *movement_component = ent->get_movement_component();

	DamageableComponent *damageable_component = ent->get_damageable_component();
	if(damageable_component && damageable_component->is_dead()) return; // Prevent playing new animation if entity is dead

	if(movement_component && movement_component->is_currently_moving()) {
		play_walk_animation();
	} else {
		play_idle_animation();
	}
}

bool VisualComponent3D::is_currently_playing_death_animation() {
	return false;
}

void VisualComponent3D::play_death_animation() {
	ERR_FAIL_NULL(animation_player);
	animation_player->stop();
	animation_player->play(get_death_animation_name());
	animation_player->advance(0);
	animation_state = AnimationState::DEAD;
}

void VisualComponent3D::_on_entity_death(const Ref<DamageObject>& damage_object) {
	play_death_animation();
}

void VisualComponent3D::_on_owner_movement_state_change(bool is_moving) {
	ERR_FAIL_NULL(animation_player);
	if(get_walk_animation_name() == animation_player->get_current_animation() || get_idle_animation_name() == animation_player->get_current_animation()) return;

	Entity *ent = get_owning_entity();
	ERR_FAIL_NULL(ent);

	MovementComponent *movement_component = ent->get_movement_component();
	ERR_FAIL_NULL(movement_component);
	
	animation_player->stop();
	if(movement_component->is_currently_moving()) {
		play_walk_animation();
	} else {
		play_idle_animation();
	}
}

void VisualComponent3D::play_idle_animation() {
	ERR_FAIL_NULL(animation_player);
	animation_player->stop();
	animation_player->play(get_idle_animation_name());
	animation_player->advance(0);
	animation_state = AnimationState::IDLE;
}

void VisualComponent3D::play_walk_animation() {
	ERR_FAIL_NULL(animation_player);
	animation_player->stop();
	animation_player->play(get_walk_animation_name());
	animation_player->advance(0);
	animation_state = AnimationState::WALK;
}

void VisualComponent3D::set_idle_animation_name(const StringName& new_idle_animation_name) {
	idle_animation_name = new_idle_animation_name;
}

StringName VisualComponent3D::get_idle_animation_name() {
	return idle_animation_name;
}

void VisualComponent3D::set_walk_animation_name(const StringName& new_walk_animation_name) {
	walk_animation_name = new_walk_animation_name;
}

StringName VisualComponent3D::get_walk_animation_name() {
	return walk_animation_name;
}

//Maybe use different replicator for components and status effects?
void VisualComponent3D::_init() {

}

void VisualComponent3D::set_death_animation_name(const StringName& new_death_animation_name) {
	death_animation_name = new_death_animation_name;
}

StringName VisualComponent3D::get_death_animation_name() {
	return death_animation_name;
}

void VisualComponent3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_animation_player"), &VisualComponent3D::get_animation_player);
    ClassDB::bind_method(D_METHOD("set_animation_player", "animation_player"), &VisualComponent3D::set_animation_player);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "animation_player", PROPERTY_HINT_NODE_TYPE, AnimationPlayer::get_class_static()), "set_animation_player", "get_animation_player");

	ClassDB::bind_method(D_METHOD("get_idle_animation_name"), &VisualComponent3D::get_idle_animation_name);
    ClassDB::bind_method(D_METHOD("set_idle_animation_name", "idle_animation_name"), &VisualComponent3D::set_idle_animation_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "idle_animation_name"), "set_idle_animation_name", "get_idle_animation_name");

	ClassDB::bind_method(D_METHOD("get_walk_animation_name"), &VisualComponent3D::get_walk_animation_name);
    ClassDB::bind_method(D_METHOD("set_walk_animation_name", "walk_animation_name"), &VisualComponent3D::set_walk_animation_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "walk_animation_name"), "set_walk_animation_name", "get_walk_animation_name");

	ClassDB::bind_method(D_METHOD("get_death_animation_name"), &VisualComponent3D::get_death_animation_name);
    ClassDB::bind_method(D_METHOD("set_death_animation_name", "death_animation_name"), &VisualComponent3D::set_death_animation_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "death_animation_name"), "set_death_animation_name", "get_death_animation_name");
}

void VisualComponent3D::play_animation_override(const String& animation_name) {
	ERR_FAIL_NULL_MSG(animation_player, "VisualComponent cannot play animation - Missing AnimationPlayer");

	animation_player->stop();
	animation_player->play_animation_from_any_library(animation_name);
	animation_state = AnimationState::OVERRIDE;
}

void VisualComponent3D::set_animation_player(AnimationPlayer *new_animation_player) {
	animation_player = (AdvancedAnimationPlayer *)new_animation_player;
}

AnimationPlayer *VisualComponent3D::get_animation_player() {
	return animation_player;
}