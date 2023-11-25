#if !defined(DAMAGE_OBJECT_HPP_INCLUDED)
#define DAMAGE_OBJECT_HPP_INCLUDED

#include <core/object/ref_counted.h>
#include "damage_inflictor_component.h"

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
    DamageInflictorComponent *inflictor = nullptr;
    //TODO: Type of origin - What exactly caused damage? Ability, attack, enviroment?
    DamagingInstance *origin;
public:
    DamageObject(DamageType _type, float _value, DamageInflictorComponent *_inflictor)
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
