#if !defined(MERCENARY_REGISTRY_INCLUDED)
#define MERCENARY_REGISTRY_INCLUDED

#include "registry.h"
#include <shared/entities/mercenaries/mercenary.hpp>

class MercenaryRegistry : public Registry<Mercenary> {
GDCLASS(MercenaryRegistry, Object);
protected:
    static void _bind_methods();
public:
    static MercenaryRegistry *get_singleton() {
        // NOTE: Not sure If It is safe
        return static_cast<MercenaryRegistry *>(Registry<Mercenary>::get_singleton());
    }
};

//MercenaryRegistry *MercenaryRegistry::singleton = nullptr;


#endif // MERCENARY_REGISTRY_INCLUDED
