#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include <shared/data_holders/use_context.hpp>
#include <core/string/ustring.h>
#include <shared/helpers/object_ptr.h>
#include <shared/core/systems/gameplay/gameplay_attributes.h>

class AbilityUseRCL;

/**
 * Class responsible for logic and data behind Abilities of mercenaries, items, etc.
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

class Ability : public Node
{
GDCLASS(Ability, Node);
protected:
    /**
     * Current cooldown of ability in ticks
    */
    int curr_cooldown = 0;
    /**
     * Base cooldown of this ability
    */
    int max_cooldown = 1;

    int cost = 0;

    GameplayAttributes ability_data;
    
    Ref<Texture2D> icon;

    AbilityUseRCL* ability_use_chain;

    virtual void use_impl(UseContext& use_context){};

    virtual void ready_impl(){};
    void ready(){ready_impl();};

public:
    int get_current_cooldown();
    int get_max_cooldown();
    bool is_on_cooldown();
    int get_cost();
    void set_cost(int cost);

    /**
     * Uses ability if possible. Returns AbilityCastError value depending on what happened.
    */
    Error use(Dictionary use_context);

    /**
     * Ability preparation - Here should go initialization code such as setting up helper nodes
    */
    virtual void onCast(){};
    virtual void tick_impl(){};
    virtual void onCooldownChange(){};

    void tick();

    //Owner changed - You might want to do some initialization/cleanup here
    virtual void set_owner_callback(){};

    Entity* get_owner();

    Ability();
};

#endif // ABILITY_HPP_INCLUDED
