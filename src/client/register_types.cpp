/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#include "register_types.h"

#include <gdextension_interface.h>

#include <core/class_db.hpp>
#include <core/defs.hpp>
#include <godot.hpp>

#include "game.hpp"
#include "client.hpp"
#include "entities/entity.hpp"
#include "game_camera.hpp"
#include "game_map.hpp"
#include "entities/mercenaries/mercenary.hpp"

using namespace godot;

void initialize_client(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

    ClassDB::register_class<Game>();
    ClassDB::register_class<Client>();
    ClassDB::register_class<Entity>();
    ClassDB::register_class<GameCamera>();
    ClassDB::register_class<GameMap>();
	ClassDB::register_class<Mercenary>();
}

void uninitialize_client(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT client_init(const GDExtensionInterface *p_interface, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_initializer(initialize_client);
	init_obj.register_terminator(uninitialize_client);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
