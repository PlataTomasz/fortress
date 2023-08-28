#if !defined(DAMAGE_OBJECT_HPP_INCLUDED)
#define DAMAGE_OBJECT_HPP_INCLUDED

#include <core/object/object.h>
#include <shared/helpers/object_ptr.h>

class Entity;

enum DamageType
{
    DAMAGE_PHYSICAL = 1,
    DAMAGE_MAGICAL = 2,
    DAMAGE_TRUE = 3,
};

VARIANT_ENUM_CAST(DamageType);

class DamageObject : public RefCounted
{
GDCLASS(DamageObject, RefCounted);
public:
    DamageType type;
    float value = 0;
    Entity *inflictor = nullptr;
    //TODO: Type of origin - What caused damage?
    //origin;
public:
    DamageObject(DamageType _type, float _value, Entity *_inflictor)
        : type(_type), value(_value), inflictor(_inflictor)
    {

    };

    DamageObject(DamageObject& other)
    {
        type = other.type;
        value = other.value;
        inflictor = other.inflictor;
    }
};

#endif // DAMAGE_OBJECT_HPP_INCLUDED
