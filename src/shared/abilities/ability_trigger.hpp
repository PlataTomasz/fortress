#if !defined(ABILITY_TRIGGER_HPP)
#define ABILITY_TRIGGER_HPP

#include <client/game_logic/abilities/active_ability.hpp>
#include <client/game_logic/abilities/passive_ability.hpp>

/**
 * Representation of ability usable by mercenary
*/
class AbilityTrigger
{
protected:
    ActiveAbility* active_ability;
    PassiveAbility* passive_ability;
public:
    AbilityTrigger(ActiveAbility* active_ability, PassiveAbility* passive_ability = nullptr)
    {
        this->active_ability = active_ability;
        this->passive_ability = passive_ability;
    }
};

#endif // ABILITY_TRIGGER_HPP
