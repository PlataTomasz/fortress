#if !defined(DOT_BEHAVIOUR_HPP)
#define DOT_BEHAVIOUR_HPP

#include <cstdio>
#include "status_effect_behaviour.hpp"

class DotStatusEffectBehaviour : public StatusEffectBehaviour
{
public:
    /**
    * Called when status wears off
    */
    virtual void onExpire()
    {
        printf("Dot effect expired!");
    };
    /**
    * Called when status is applied to entity
    */
    virtual void onApply()
    {
        printf("Dot effect applied!");
    };
    /**
    * Called every process frame
    */
    virtual void onProcessFrame()
    {
        printf("Dot effect process frame!")
    };
};

#endif // DOT_BEHAVIOUR_HPP
