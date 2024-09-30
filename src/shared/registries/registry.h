#if !defined(REGISTRY_INCLUDED)
#define REGISTRY_INCLUDED

#include <core/object/object.h>
#include <scene/resources/packed_scene.h>
#include <core/io/dir_access.h>

#include <type_traits>

template<class T>
class Registry : public Object{
protected:
    static_assert(std::is_base_of<Node, T>(), "Registry works only with Nodes!");

    static Registry<T> *singleton;
    HashMap<StringName, Ref<PackedScene>> registered_objects;
    
    // TODO: Move out of registry class - Registry shouldn't be responsible for loading external data
    void load_from_directory(const String& path) {
        Error diraccess_err = OK;
        Ref<DirAccess> directory_access = DirAccess::open(path, &diraccess_err);
        ERR_FAIL_COND_MSG(diraccess_err != OK, "Directory access error occured at initialization. Registry might be incomplete.");

        PackedStringArray file_names = directory_access->get_files();

        for(const String &filename : file_names) {
            Ref<PackedScene> packed_status_effect = ResourceLoader::load(path + filename, PackedScene::get_class_static());
            ERR_FAIL_COND(packed_status_effect.is_null());

            Ref<SceneState> scene_state = packed_status_effect->get_state();
            // HACK: Temp fix untill I'll figure out why It's wrong
            //ERR_FAIL_COND_MSG(scene_state->get_node_type(0) == T::get_class_static(), "Register of " + filename + " failed. PackedScene doesn't have " + T::get_class_static() + " as scene root!");
            PackedStringArray filename_split = filename.split(".");
            ERR_FAIL_COND(filename_split.size() < 1);
            String filename_no_extension = filename_split[0];
            registered_objects.insert(filename_no_extension, packed_status_effect);
        }
    }
public:
    static Registry<T> *get_singleton() {
        if(!singleton) {
            singleton = new Registry<T>();
            singleton->load_from_directory(get_initial_data_path());
        }
        return singleton;
    }

    static String get_initial_data_path();

    T *create_instance(const StringName& name) {
        T *status_effect_instance = static_cast<T *>(registered_objects.has(name) ? registered_objects.get(name)->instantiate() : nullptr);
        return status_effect_instance;
    }

    PackedStringArray get_registered_names() {
        PackedStringArray names;
        names.resize(registered_objects.size());

        // Copy keys from HashMap to Vector as values
        int i = 0;
        for(const KeyValue<StringName, Ref<PackedScene>> &registered : registered_objects) {
            names.set(i, registered.key.operator String());
            i++;
        }

        return names;
    }

    bool has(const String& key) {
        return registered_objects.has(key);
    }
};

#endif // REGISTRY_INCLUDED
