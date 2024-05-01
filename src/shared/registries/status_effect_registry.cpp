#include "status_effect_registry.h"

#include <core/io/dir_access.h>
#include <shared/status_effects/status_effect.hpp>

StatusEffectRegistry *StatusEffectRegistry::singleton = nullptr;

StatusEffectRegistry *StatusEffectRegistry::get_singleton() {
    if(!singleton)
    {
        singleton = new StatusEffectRegistry();
        singleton->load_from_directory("res://status_effects/");
    }
    return singleton;
}

void StatusEffectRegistry::load_from_directory(const String& path) {
    Error diraccess_err = OK;
    Ref<DirAccess> directory_access = DirAccess::open(path, &diraccess_err);
    ERR_FAIL_COND_MSG(diraccess_err != OK, "Directory access error occured at initialization. Registry might be incomplete.");

    PackedStringArray file_names = directory_access->get_files();

    for(const String &filename : file_names) {
        Ref<PackedScene> packed_status_effect = ResourceLoader::load(path + filename, "PackedScene");
        ERR_FAIL_COND(packed_status_effect.is_null());

        Ref<SceneState> scene_state = packed_status_effect->get_state();

        ERR_FAIL_COND_MSG(scene_state->get_node_type(0) == "StatusEffect", "Register of " + filename + " failed. PackedScene doesn't have StatusEffect as scene root!");
        PackedStringArray filename_split = filename.split(".");
        ERR_FAIL_COND(filename_split.size() < 1);
        String filename_no_extension = filename_split[0];
        registered_objects.insert(filename_no_extension, packed_status_effect);
    }
    print_line(get_registered_names());
}

PackedStringArray StatusEffectRegistry::get_registered_names() {
    PackedStringArray names;
    names.resize(registered_objects.size());

    for(const KeyValue<String, Ref<PackedScene>> &registered : registered_objects) {
        names.append(registered.key);
    }

    return names;
}

StatusEffect *StatusEffectRegistry::create_instance(const String& name) {
    StatusEffect *status_effect_instance = static_cast<StatusEffect *>(registered_objects.has(name) ? registered_objects.get(name)->instantiate() : nullptr);

    return status_effect_instance;
}