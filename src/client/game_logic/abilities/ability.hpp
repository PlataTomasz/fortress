#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include <client/game_logic/abilities/use_context.hpp>
#include <core/string/ustring.h>

class AbilityUseRCL;

/**
 * ClassC responsible for logic and data behind Abilities of mercenaries, items, etc.
*/

enum AbilityUseError
{
    SUCCESS = 0,
    //These two can never occur simulatenously
    INVALID_TARGET = 1,
    TARGET_OUT_OF_RANGE = 1<<1,

    NOT_ENOUGH_RESOURCE = 1<<2,
    ABILITY_ON_COOLDOWN = 1<<3
};

class Ability
{
protected:

    Entity* owner;
    String name;

    /**
     * Current cooldown of ability in ticks
    */
    int curr_cooldown = 0;
    /**
     * Base cooldown of this ability
    */
    int max_cooldown = 1;

    int cost = 0;

    AbilityUseRCL* ability_use_chain;

    virtual void use_impl(UseContext use_context) = 0;

    virtual void setup_ability_use_chain();

public:
    int get_current_cooldown();
    int get_max_cooldown();
    bool is_on_cooldown();
    int get_cost();
    void set_cost(int cost);

    /**
     * Uses ability if possible. Returns AbilityCastError value depending on what happened.
    */
    AbilityUseError use(UseContext use_context);

    /**
     * Uses ability completly ignoring anything that would prevent it
    */
    void force_use(UseContext use_context);

    /**
     * Checks if ability can be used. Returns 0 if yes, AbilityCastError value otherwise
    */
    AbilityUseError can_use(UseContext use_context);

    /**
     * Ability preparation - Here should go initialization code such as setting up helper nodes
    */
    virtual void initialize(){};
    virtual void onCast(){};
    virtual void onTick(){};
    virtual void onCooldownChange(){};

    void set_owner(Entity* owner);
    Entity* get_owner();

    Ability();
    Ability(Entity* owner);
};

#endif // ABILITY_HPP_INCLUDED
