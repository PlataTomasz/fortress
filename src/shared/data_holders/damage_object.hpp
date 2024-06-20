#if !defined(DAMAGE_OBJECT_INCLUDED)
#define DAMAGE_OBJECT_INCLUDED

#include <core/object/ref_counted.h>
#include <shared/entities/entity.h>

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
    enum DamageSubtype {
        NONE = 0,
        BASIC_ATTACK_DAMAGE = 1,
        ABILITY_DAMAGE = 1 << 1,
        OVER_TIME_DAMAGE = 1 << 2,
        AREA_DAMAGE = 1 << 3
    };

    DamageType type;
    int subtype;

    float value = 0;
    Entity *attacker = nullptr;
    //TODO: Type of origin - What exactly caused damage? Ability, attack, enviroment?
    //DamagingInstance *origin;
public:
    DamageType get_type() {
        return type;
    }

    int get_subtype() {
        return subtype;
    }

    float get_value() {
        return value;
    }

    Entity *get_attacker() {
        return attacker;
    }

    DamageObject(DamageType _type, int _subtype, float _value, ObjectPtr<Entity> _attacker)
        : type(_type), subtype(_subtype), value(_value), attacker(_attacker)
    {

    };
};

VARIANT_ENUM_CAST(DamageObject::DamageType);

#endif // DAMAGE_OBJECT_INCLUDED
