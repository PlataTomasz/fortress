//Godot
#include <godot/gdnative_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "game.hpp"
#include "client.h"
#include "entities/entity.hpp"

using namespace godot;

void initialize_client(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }

    ClassDB::register_class<Game>();
    ClassDB::register_class<Client>();
    ClassDB::register_class<Entity>();
}

void uninitialize_client(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }
}

int main()
{
    return 0;
}

extern "C" {

// Initialization.

GDNativeBool GDN_EXPORT cl_entrypoint(const GDNativeInterface *p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_initializer(initialize_client);
	init_obj.register_terminator(uninitialize_client);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
