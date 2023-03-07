#if !defined(DAMAGE_OBJECT_HPP_INCLUDED)
#define DAMAGE_OBJECT_HPP_INCLUDED

class Entity;

enum DamageType
{
    DAMAGE_PHYSICAL = 1,
    DAMAGE_MAGICAL = 2,
    DAMAGE_TRUE = 3,
};

struct DamageObject
{
    DamageType type;
    double value;
    Entity* inflictor;
    //TODO: Type of origin - What caused damage?
    //origin;
};

#endif // DAMAGE_OBJECT_HPP_INCLUDED
