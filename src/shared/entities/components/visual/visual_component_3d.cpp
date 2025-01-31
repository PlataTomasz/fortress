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

			DamageableComponent *damageable = ent->get_damageable_component();
			if(damageable) {
				damageable->connect("death", callable_mp(this, &VisualComponent3D::_on_entity_death));
				damageable->connect("revived", callable_mp(this, &VisualComponent3D::_on_entity_revive));
			}

			animation_state = new IdleAnimationState(this);
			animation_state->play_animation();
		}
		break;

		default:
			break;
	}
}

void VisualComponent3D::_on_movement_start() {
	AnimationState *old_animation_state = animation_state;
	animation_state = animation_state->on_start_walking();
	animation_state->play_animation();
	delete old_animation_state;
}

void VisualComponent3D::_on_movement_finish() {
	AnimationState *old_animation_state = animation_state;
	animation_state = animation_state->on_stop_walking();
	animation_state->play_animation();
	delete old_animation_state;
}

Entity *VisualComponent3D::get_owning_entity() {
    return Object::cast_to<Entity>(get_parent());
}

void VisualComponent3D::play_idle_animation() {
	ERR_FAIL_NULL(animation_player);
	animation_player->stop();
	animation_player->play(get_idle_animation_name());
	animation_player->advance(0);
}

void VisualComponent3D::play_walk_animation() {
	ERR_FAIL_NULL(animation_player);
	animation_player->stop();
	animation_player->play(get_walk_animation_name());
	animation_player->advance(0);
}

void VisualComponent3D::_on_animation_finish(const String& animation_name) {
	Entity *owning_entity = get_owning_entity();
	ERR_FAIL_NULL(owning_entity);
	MovementComponent *movement_component = owning_entity->get_movement_component();
	bool is_currently_walking = movement_component && movement_component->is_currently_moving() ? true : false;
	AnimationState *old_animation_state = animation_state;
	animation_state = animation_state->on_animation_finish(is_currently_walking);
	animation_state->play_animation();
	delete old_animation_state;
}

bool VisualComponent3D::is_currently_playing_death_animation() {
	return false;
}

void VisualComponent3D::play_death_animation() {
	ERR_FAIL_NULL(animation_player);
	animation_player->stop();
	animation_player->play(get_death_animation_name());
	animation_player->advance(0);
}

void VisualComponent3D::_on_entity_death(const Ref<DamageObject>& damage_object) {
	AnimationState *old_animation_state = animation_state;
	animation_state = animation_state->on_death();
	animation_state->play_animation();
	delete old_animation_state;
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
	AnimationState *old_animation_state = animation_state;
	animation_state = animation_state->on_animation_override(animation_name);
	animation_state->play_animation();
	delete old_animation_state;
}

void VisualComponent3D::play_named_animation(const StringName& animation_name) {
	animation_player->play_animation_from_any_library(animation_name);
}

void VisualComponent3D::set_animation_player(AnimationPlayer *new_animation_player) {
	animation_player = (AdvancedAnimationPlayer *)new_animation_player;
}

AnimationPlayer *VisualComponent3D::get_animation_player() {
	return animation_player;
}

void VisualComponent3D::_on_entity_revive() {
	AnimationState *old_animation_state = animation_state;
	animation_state = animation_state->on_respawn();
	animation_state->play_animation();
	delete old_animation_state;
}
