#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <string>

class Entity;
class StatusEffectBehaviour
{
public:
    /**
     * Called when status wears off
    */
    virtual void onExpire(StatusEffectData *statusEffectData);
    /**
     * Called when status is applied to entity
    */
    virtual void onApply(StatusEffectData *statusEffectData);
    /**
     * Called every process frame
    */
    virtual void onProcessFrame(StatusEffectData *statusEffectData);
};


/**
 * Stores initial properties of the buff. Most of them are read only.
*/
class StatusEffectData
{
protected:

    enum StatusEffectFlags
    {
        IS_DEBUFF = 1,
        IS_DAMAGING = 1 << 1,
        IS_HEALING = 1 << 2,
        IS_CROWD_CONTROL = 1 << 3,
    } uint16_t;

    const std::string name;
    /**
     * Initial max durration of status effect in frames
    */
    int maxDuration;

    StatusEffectData::StatusEffectFlags statusEffectFlags;


    //Store function pointers? - Or pointer to object storing functions?
    StatusEffectBehaviour *statusEffectBehaviour;

public:
    std::string getName();

    StatusEffectData(const char *_name, int maxStacks, int damage, int durration) : name{_name}
    {
        
    }
};

class StatusEffect
{
protected:
    /**
     * How much frames need to pass before status effect expires?
    */
    int currentDuration;
    int maxDuration;

    /**
     * Who has the status?
    */
    Entity *target;
    /**
     * Who inflicted status?
    */
    Entity *inflictor;

    const StatusEffectData *statusEffectData;

public:
    /**
     * Called when status wears off
    */
    void onExpire();
    /**
     * Called when status is applied to entity
    */
    void onApply();
    /**
     * Called every process frame
    */
    void onProcessFrame();

    StatusEffect(StatusEffectData *statusEffectData, float durration, Entity *inflictor){};
    //Read from file constructor
    StatusEffect(){};
};

#endif // STATUS_EFFECT_HPP
