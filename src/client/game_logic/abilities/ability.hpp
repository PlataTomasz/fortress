#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include "cast_context.hpp"

enum AbilityCastError
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
    CastContext castContext;
    /**
     * Current cooldown of ability in ticks
    */
    int curr_cooldown;
    /**
     * Base cooldown of this ability
    */
    int max_cooldown;
public:
    int get_current_cooldown()
    {
        return this->curr_cooldown;
    }

    int get_max_cooldown()
    {
        return this->max_cooldown;
    }

    bool is_on_cooldown()
    {
        return this->curr_cooldown > 0;
    }

    AbilityCastError can_cast(CastContext *cast_context)
    {

    }


    void setCastContext(CastContext &castContext)
    {
        this->castContext = castContext;
    };

    virtual void initialize(){};
    virtual void onCast(){};
    virtual void onTick(){};
    virtual void onCooldownChange(){};
    
};

#endif // ABILITY_HPP_INCLUDED
