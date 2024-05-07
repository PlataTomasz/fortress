#if !defined(STATUS_EFFECT_REGISTRY_INCLUDED)
#define STATUS_EFFECT_REGISTRY_INCLUDED

#include <core/object/object.h>
#include <scene/resources/packed_scene.h>

#include <shared/status_effects/status_effect.hpp>
#include "registry.h"

//Declared like this to workaround GDCLASS macro in template class, so It can be exposed to Engine/GDScript
class StatusEffectRegistry : public Registry<StatusEffect> {
GDCLASS(StatusEffectRegistry, Object);
protected:
    static void _bind_methods();
};

#endif // STATUS_EFFECT_REGISTRY_INCLUDED
