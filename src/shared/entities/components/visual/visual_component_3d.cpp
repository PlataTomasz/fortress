#include "visual_component_3d.h"

#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/3d/primitive_meshes.h>
#include <shared/entities/entity.h>
#include <shared/entities/components/movement/movement_component.h>

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
			ERR_FAIL_NULL(movement_component);

			movement_component->connect("currently_moving_changed", callable_mp(this, &VisualComponent3D::_on_owner_movement_state_change));

			ERR_FAIL_NULL(animation_player);
			animation_player->connect("current_animation_changed", callable_mp(this, &VisualComponent3D::_on_animation_finish));
		}
		break;

		default:
			break;
	}
}

Entity *VisualComponent3D::get_owning_entity() {
    return Object::cast_to<Entity>(get_parent());
}

void VisualComponent3D::switch_to_idle_animation() {
	ERR_FAIL_NULL(animation_player);

	animation_player->queue_from_any_library("idle");
	animation_state = AnimationState::IDLE;
}

void VisualComponent3D::switch_to_walk_animation() {
	ERR_FAIL_NULL(animation_player);

	animation_player->queue_from_any_library("walk");
	animation_state = AnimationState::WALK;
}

void VisualComponent3D::_on_animation_finish(const String& animation_name) {
		if(animation_state == AnimationState::OVERRIDE) {
		Entity *ent = get_owning_entity();
		ERR_FAIL_NULL(ent);

		MovementComponent *movement_component = ent->get_movement_component();
		ERR_FAIL_NULL(movement_component);

		if(movement_component->is_currently_moving()) {
			switch_to_walk_animation();
		} else {
			switch_to_idle_animation();
		}
	}
}

void VisualComponent3D::_on_owner_movement_state_change(bool is_moving) {
	Entity *ent = get_owning_entity();
	ERR_FAIL_NULL(ent);

	MovementComponent *movement_component = ent->get_movement_component();
	ERR_FAIL_NULL(movement_component);

	if(animation_state == AnimationState::IDLE && is_moving) {
		switch_to_walk_animation();
	} else if (animation_state == AnimationState::WALK && !is_moving) {
		switch_to_idle_animation();
	}
}

//Maybe use different replicator for components and status effects?
void VisualComponent3D::_init() {

}

void VisualComponent3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_animation_player"), &VisualComponent3D::get_animation_player);
    ClassDB::bind_method(D_METHOD("set_animation_player", "animation_player"), &VisualComponent3D::set_animation_player);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "animation_player", PROPERTY_HINT_NODE_TYPE, AnimationPlayer::get_class_static()), "set_animation_player", "get_animation_player");
}

void VisualComponent3D::play_animation_override(const String& animation_name) {
	ERR_FAIL_NULL_MSG(animation_player, "VisualComponent cannot play animation - Missing AnimationPlayer");

	animation_player->play_animation_from_any_library(animation_name);
	animation_state = AnimationState::OVERRIDE;
}

void VisualComponent3D::set_animation_player(AnimationPlayer *new_animation_player) {
	animation_player = (AdvancedAnimationPlayer *)new_animation_player;
}

AnimationPlayer *VisualComponent3D::get_animation_player() {
	return animation_player;
}