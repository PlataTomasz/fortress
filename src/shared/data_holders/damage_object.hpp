#if !defined(DAMAGE_OBJECT_HPP_INCLUDED)
#define DAMAGE_OBJECT_HPP_INCLUDED

#include <core/object/ref_counted.h>
#include <shared/entities/components/damage/damage_inflictor_component.h>

VARIANT_ENUM_CAST(DamageObject::DamageType);

class DamageObject : public RefCounted
{
GDCLASS(DamageObject, RefCounted);
public:
    enum DamageType
    {
        DAMAGE_PHYSICAL = 1,
        DAMAGE_MAGICAL = 2,
        DAMAGE_TRUE = 3,
    };
    DamageType type;
    float value = 0;
    ObjectPtr<Entity> inflictor = nullptr;
    //TODO: Type of origin - What exactly caused damage? Ability, attack, enviroment?
    //DamagingInstance *origin;
public:
    DamageObject(DamageType _type, float _value, ObjectPtr<Entity> _inflictor)
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
