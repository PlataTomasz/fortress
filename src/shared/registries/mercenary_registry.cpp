#include "mercenary_registry.h"

template<>
Registry<Mercenary> *Registry<Mercenary>::singleton = nullptr; 

// Define data registry path
template<>
String Registry<Mercenary>::get_initial_data_path() {
    return "res://entities/mercenaries/";
}

void MercenaryRegistry::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_registered_names"), &MercenaryRegistry::get_registered_names);
    ClassDB::bind_static_method(get_class_static(), D_METHOD("get_singleton"), &MercenaryRegistry::get_singleton);
}