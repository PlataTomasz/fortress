#include "status_effect.hpp"
#include "../entities/entity.hpp"

String StatusEffectData::getName()
{
    return name;
}

StatusEffectData::operator String() const
{
    return "Damage: " + damage;
}