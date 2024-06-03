#include "entity_registry.h"

template<>
Registry<Entity> *Registry<Entity>::singleton = nullptr; 

// Define data registry path
template<>
String Registry<Entity>::get_initial_data_path() {
    return "res://entities/";
}

void EntityRegistry::_bind_methods() {
    ClassDB::bind_static_method(get_class_static(), D_METHOD("get_initial_data_path"), &EntityRegistry::get_initial_data_path);
}