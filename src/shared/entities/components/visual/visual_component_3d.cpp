#include "visual_component_3d.h"

#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/3d/primitive_meshes.h>

void VisualComponent3D::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			break;

		default:
			break;
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

void VisualComponent3D::play_animation(const String& animation_name) {
	ERR_FAIL_NULL_MSG(animation_player, "VisualComponent cannot play animation - Missing AnimationPlayer");

	// Play animation if it exist in any animation library
	List<StringName> animation_libraries;
	animation_player->get_animation_library_list(&animation_libraries);
	for(StringName animation_library_name : animation_libraries) {
		Ref<AnimationLibrary> animation_library = animation_player->get_animation_library(animation_library_name);

		animation_library->get_animation(animation_name);

		if(animation_library->has_animation(animation_name)) {
			if(animation_library_name == StringName()) {
				animation_player->play(String(animation_name));
			} else {
				animation_player->play(String(animation_library_name) + "/" + animation_name);
			}

			// FIXME: Temporary; will break if additional animation libraries are used
			animation_player->queue("Walk002"); // Play walk animation once this animation finishes
			break;
		}
	}
}

void VisualComponent3D::set_animation_player(AnimationPlayer *new_animation_player) {
	animation_player = new_animation_player;
}

AnimationPlayer *VisualComponent3D::get_animation_player() {
	return animation_player;
}