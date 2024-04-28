#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include <shared/data_holders/action_context.hpp>
#include <core/string/ustring.h>
#include <shared/helpers/object_ptr.h>
#include <shared/core/systems/gameplay/gameplay_attributes.h>

#include <core/string/node_path.h>

class Timer;

/**
 * Class responsible for logic and data behind Abilities of mercenaries, items, etc.
*/
class Ability : public Node
{
GDCLASS(Ability, Node);
private:
    void _ready();
public:
    NodePath cooldown_timer_path;
    Timer *cooldown_timer = nullptr;

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

    String displayed_name;
    String displayed_description;

    // Internal use: Without most checks
    virtual void _use(const Ref<ActionContext>& action_context){};

    static void _bind_methods();

    void _notification(int p_notification);

    NodePath get_cooldown_timer_path();
    void set_cooldown_timer_path(const NodePath& p_cooldown_timer_path);

    Timer *get_cooldown_timer();
public:
    float get_current_cooldown();
    float get_max_cooldown();
    bool is_on_cooldown();

    Ref<Texture2D> get_icon();
    void set_icon(const Ref<Texture2D> &new_icon);

    String get_displayed_description();
    void set_displayed_description(const String &new_description);

    String get_displayed_name();
    void set_displayed_name(const String &new_name);

    AbilityUseError use_check(const Ref<ActionContext>& action_context);
    void force_use(const Ref<ActionContext>& action_context);

    /**
     * Uses this ability if possible. Returns AbilityCastError value depending on what happened.
    */
    AbilityUseError use(const Ref<ActionContext>& action_context);

    Entity* get_owner();

    Ability();
};

VARIANT_ENUM_CAST(Ability::AbilityUseError);

#endif // ABILITY_HPP_INCLUDED
