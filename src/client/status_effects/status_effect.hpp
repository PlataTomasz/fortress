#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>

class Entity;
class StatusEffectBehaviour;

/**
 * Class storing status effect data. Most likely read from file.
*/
class StatusEffectData
{
protected:

    String name;
    int maxStacks;
    /**
    * Initial max durration of status effect in frames
    */
    int duration;
    int damage;

    /**
     * Object that stores method pointers to be called on this object.
    */
    StatusEffectBehaviour *statusEffectBehaviour;

public:
    operator String() const;

    

    String getName();

    StatusEffectData(String _name, int maxStacks, int damage, int durration) : name{_name}
    {
        
    }
};

/**
 * Class representing currently applied status effect
*/
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

    StatusEffect(StatusEffectData *statusEffectData, float duration, Entity *inflictor){};
    //Read from file constructor
    StatusEffect(){};
};

#endif // STATUS_EFFECT_HPP
