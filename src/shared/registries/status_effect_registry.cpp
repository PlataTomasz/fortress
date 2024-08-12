#include "status_effect_registry.h"

template<>
Registry<StatusEffect> *Registry<StatusEffect>::singleton = nullptr;

// Define data registry path
template<>
String Registry<StatusEffect>::get_initial_data_path() {
    return "res://status_effects/";
}

void StatusEffectRegistry::_bind_methods() {
    ClassDB::bind_static_method(get_class_static(), D_METHOD("get_initial_data_path"), &StatusEffectRegistry::get_initial_data_path);
}