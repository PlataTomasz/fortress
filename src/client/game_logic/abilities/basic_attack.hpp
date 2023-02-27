#if !defined(BASIC_ATTACK_HPP_INCLUDED)
#define BASIC_ATTACK_HPP_INCLUDED

#include <client/game_logic/abilities/ability.hpp>
#include <classes/area3d.hpp>

/**
 * Ability representing basic attack of entity.
*/
class BasicAttackAbility : public Ability
{
protected:
    Area3D* hitbox;
public:
    void use_impl(UseContext use_context) override;
};

#endif // BASIC_ATTACK_HPP_INCLUDED
