#if !defined(DAMAGE_OBJECT_BUILDER_INCLUDED)
#define DAMAGE_OBJECT_BUILDER_INCLUDED

#include <shared/data_holders/damage_object.hpp>

class DamageObject;

class DamageObjectBuilder {
private:
    DamageObject::DamageType _damage_type;
    int _damage_subtype;
    float _damage_value = 0;
    Entity *_attacker = nullptr;
public:
    DamageObjectBuilder &damage_type(DamageObject::DamageType new_type);

    DamageObjectBuilder &damage_subtype_basic_attack();
    DamageObjectBuilder &damage_subtype_ability();
    DamageObjectBuilder &damage_subtype_area();
    DamageObjectBuilder &damage_subtype_self();
    DamageObjectBuilder &damage_subtype_over_time();

    DamageObjectBuilder &value(float new_value);
    DamageObjectBuilder &attacker(Entity *new_attacker);

    DamageObject *build();

};

#endif // DAMAGE_OBJECT_BUILDER_INCLUDED
