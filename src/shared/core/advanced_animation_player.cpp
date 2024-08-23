#include "advanced_animation_player.h"

void AdvancedAnimationPlayer::play_animation_from_any_library(const String& animation_name) {
	// Play animation if it exist in any animation library
	List<StringName> animation_libraries;
	get_animation_library_list(&animation_libraries);
	for(StringName animation_library_name : animation_libraries) {
		Ref<AnimationLibrary> animation_library = get_animation_library(animation_library_name);

		animation_library->get_animation(animation_name);

		if(animation_library->has_animation(animation_name)) {
			if(animation_library_name == StringName()) {
				play(String(animation_name));
			} else {
				play(String(animation_library_name) + "/" + animation_name);
			}
		}
	}
}

void AdvancedAnimationPlayer::queue_from_any_library(const String& animation_name) {
    List<StringName> animation_libraries;
	get_animation_library_list(&animation_libraries);
	for(StringName animation_library_name : animation_libraries) {
		Ref<AnimationLibrary> animation_library = get_animation_library(animation_library_name);

		animation_library->get_animation(animation_name);

		if(animation_library->has_animation(animation_name)) {
			if(animation_library_name == StringName()) {
				queue(String(animation_name));
			} else {
				queue(String(animation_library_name) + "/" + animation_name);
			}
		}
	}
}