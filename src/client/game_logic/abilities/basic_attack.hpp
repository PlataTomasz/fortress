#if !defined(BASIC_ATTACK_HPP_INCLUDED)
#define BASIC_ATTACK_HPP_INCLUDED

#include <client/game_logic/abilities/ability.hpp>
#include <scene/3d/area_3d.h>
#include <client/game_logic/abilities/use_context.hpp>

/**
 * Ability representing basic attack of entity.
*/
class BasicAttackAbility : public Ability
{
protected:
    Area3D* hitbox;
public:
    virtual void use_impl(UseContext use_context);
    virtual void initialize(){};

    BasicAttackAbility(Entity* owner);
};

#endif // BASIC_ATTACK_HPP_INCLUDED
