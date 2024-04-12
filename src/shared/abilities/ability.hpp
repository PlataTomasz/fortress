#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include <shared/data_holders/use_context.hpp>
#include <core/string/ustring.h>
#include <shared/helpers/object_ptr.h>
#include <shared/core/systems/gameplay/gameplay_attributes.h>

/**
 * Class responsible for logic and data behind Abilities of mercenaries, items, etc.
*/
class Ability : public Node
{
GDCLASS(Ability, Node);
public:
    enum AbilityUseError
    {
        SUCCESS = 0,
        //These two can never occur simulatenously
        INVALID_TARGET = 1,
        TARGET_OUT_OF_RANGE = 1<<1,

        NOT_ENOUGH_RESOURCE = 1<<2,
        ABILITY_ON_COOLDOWN = 1<<3,
        INTERNAL_ERROR = 1<<31
    };
protected:
    /**
     * Current cooldown of ability in ticks
    */
    int curr_cooldown = 0;
    /**
     * Base cooldown of this ability
    */
    int max_cooldown = 1;

    Ref<Texture2D> icon;

    // Internal use: Without most checks
    void _use(const Ref<UseContext>& use_context){};

    static void _bind_methods();

    void _notification(int p_notification);
public:
    int get_current_cooldown();
    int get_max_cooldown();
    bool is_on_cooldown();

    virtual void _ready(){};

    AbilityUseError use_check(const Ref<UseContext>& use_context);
    void force_use(const Ref<UseContext>& use_context);

    /**
     * Uses this ability if possible. Returns AbilityCastError value depending on what happened.
    */
    AbilityUseError use(const Ref<UseContext>& use_context);

    /**
     * Ability preparation - Here should go initialization code such as setting up helper nodes
    */
    virtual void onCast(){};
    virtual void tick_impl(){};
    virtual void onCooldownChange(){};

    void tick();

    Entity* get_owner();

    Ability();
};

VARIANT_ENUM_CAST(Ability::AbilityUseError);

#endif // ABILITY_HPP_INCLUDED
