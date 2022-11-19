#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include "cast_context.hpp"

class Ability
{
protected:
    CastContext castContext;
public:
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
