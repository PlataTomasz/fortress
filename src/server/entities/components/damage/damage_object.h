#if !defined(DAMAGE_OBJECT_INCLUDED)
#define DAMAGE_OBJECT_INCLUDED

#include <core/object/ref_counted.h>

class Entity;

class DamageObject : public RefCounted
{
GDCLASS(DamageObject, RefCounted);
public:
    enum DamageType
    {
        DAMAGE_GENERIC,
        DAMAGE_TRUE,
        DAMAGE_INTERNAL
    };

    DamageType type = DAMAGE_GENERIC;
    double value = 0;
    Entity *inflictor = nullptr;
    //TODO: origin - What caused damage? Ability, enviroment, etc.?
public:
    DamageObject(DamageType _type, float _value, Entity *_inflictor)
        : type(_type), value(_value), inflictor(_inflictor)
    {

    };

    DamageObject()
    {

    }
};

VARIANT_ENUM_CAST(DamageObject::DamageType);

#endif // DAMAGE_OBJECT_INCLUDED
