#if !defined(STATUS_EFFECT_BEHAVIOUR)
#define STATUS_EFFECT_BEHAVIOUR

class StatusEffect;

/**
 * Class that stores methods which handle StatusEffect logic
*/
class StatusEffectBehaviour
{
public:
    /**
     * Called when status wears off
    */
    virtual void onExpire(StatusEffect *statusEffect){};
    /**
     * Called when status is applied to entity
    */
    virtual void onApply(StatusEffect *statusEffect){};
    /**
     * Called every process frame
    */
    virtual void onProcessFrame(StatusEffect *statusEffect){};
};

#endif // STATUS_EFFECT_BEHAVIOUR
