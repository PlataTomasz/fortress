#if !defined(ENTITY_REGISTRY_INCLUDED)
#define ENTITY_REGISTRY_INCLUDED

#include "registry.h"
#include <shared/entities/entity.h>

class EntityRegistry : public Registry<Entity> {
GDCLASS(EntityRegistry, Object);

protected:
    static void _bind_methods();
};

#endif // ENTITY_REGISTRY_INCLUDED
