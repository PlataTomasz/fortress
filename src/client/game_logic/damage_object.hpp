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

class DamageObject
{
public:
    DamageType type;
    float value = 0;
    Entity *inflictor = 0;
    //TODO: Type of origin - What caused damage?
    //origin;
private:
    bool valid = false;

public:
    bool is_valid()
    {
        return valid;
    }

    DamageObject(DamageType _type, float _value, Entity *_inflictor)
        : type(_type), value(_value), inflictor(_inflictor), valid(true)
    {

    };

    DamageObject(Dictionary dictionary)
    {
        Variant dict_type = dictionary.get_valid("type");
        Variant dict_value = dictionary.get_valid("value");
        Variant dict_inflictor = dictionary.get_valid("inflictor");

        if(
            dict_type.get_type() == Variant::OBJECT
            && dict_value.get_type() == Variant::FLOAT
            && dict_inflictor.get_type() == Variant::OBJECT
        )
        {
            type = VariantCaster<DamageType>::cast(dict_type);
            value = VariantCaster<float>::cast(dict_value);
            inflictor = VariantCaster<Entity*>::cast(dict_inflictor);
            //Successs
            valid = true;
        }
    }

    operator Dictionary()
    {
        Dictionary dict;
        dict["type"] = type;
        dict["value"] = value;
        dict["inflictor"] = inflictor;

        return dict;
    }
};

#endif // DAMAGE_OBJECT_HPP_INCLUDED
