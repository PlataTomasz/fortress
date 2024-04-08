#if !defined(STATUS_EFFECT_FACTORY_INCLUDED)
#define STATUS_EFFECT_FACTORY_INCLUDED

#include <shared/status_effects/status_effect.hpp>

class StatusEffectFactory {
static String status_effect_load_path;
public:
    // Creates new instance of status effect with specified name. If effect with such name doesn't exist, nullptr is returned
    static StatusEffect *create_status_effect(const String &status_effect_name) {
        Ref<PackedScene> status_effect_packed_scene = ResourceLoader::load(status_effect_load_path + status_effect_name + ".tscn");

        if (status_effect_packed_scene.is_valid()) {
            return static_cast<StatusEffect *>(status_effect_packed_scene->instantiate());
        } else {
            return nullptr;
        }
    }
};

String StatusEffectFactory::status_effect_load_path = "res://status_effect/";

#endif // STATUS_EFFECT_FACTORY_INCLUDED
