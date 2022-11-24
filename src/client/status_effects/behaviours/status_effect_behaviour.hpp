#if !defined(STATUS_EFFECT_BEHAVIOUR)
#define STATUS_EFFECT_BEHAVIOUR

class StatusEffect;

/**
 * Class that stores methods which handle StatusEffect logic
*/
class StatusEffectBehaviour
{
protected:
    StatusEffect *statusEffect;
public:
    /**
     * Called when status wears off
    */
    virtual void onExpire()
    {
        
    };
    /**
     * Called when status is applied to entity
    */
    virtual void onApply()
    {

    };
    /**
     * Called every process frame
    */
    virtual void onProcessFrame()
    {

    };
};

#endif // STATUS_EFFECT_BEHAVIOUR
