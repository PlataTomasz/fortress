#if !defined(STATUS_EFFECT_REGISTRY_INCLUDED)
#define STATUS_EFFECT_REGISTRY_INCLUDED

#include <core/object/object.h>
#include <scene/resources/packed_scene.h>

class StatusEffect;

class StatusEffectRegistry : public Object {
private:
    static StatusEffectRegistry *singleton;
    HashMap<String, Ref<PackedScene>> registered_objects;

    void load_from_directory(const String& path);
public:
    static StatusEffectRegistry *get_singleton();

    StatusEffect *create_instance(const String& name);
    PackedStringArray get_registered_names();
};

#endif // STATUS_EFFECT_REGISTRY_INCLUDED
