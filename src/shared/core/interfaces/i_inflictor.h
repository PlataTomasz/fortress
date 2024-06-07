#if !defined(I_INFLICTOR_INCLUDED)
#define I_INFLICTOR_INCLUDED

#include <core/variant/type_info.h>
#include <core/variant/variant.h>
#include <core/object/object.h>

class IInflictor {
    // Wheter It is basic attack, ability
    virtual void get_type();
};

// Interface workaround for godot
MAKE_TYPE_INFO(IInflictor, Variant::OBJECT);

#endif // I_INFLICTOR_INCLUDED
