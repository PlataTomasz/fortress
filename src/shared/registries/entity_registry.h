#if !defined(ENTITY_REGISTRY_INCLUDED)
#define ENTITY_REGISTRY_INCLUDED

#include "registry.h"
#include <shared/entities/entity.h>

class EntityRegistry : public Registry<Entity> {
GDCLASS(EntityRegistry, Object);
protected:
    static void _bind_methods();
public:
    static EntityRegistry *get_singleton() {
        // NOTE: Not sure If It is safe
        return static_cast<EntityRegistry *>(Registry<Entity>::get_singleton());
    }
};

#endif // ENTITY_REGISTRY_INCLUDED
