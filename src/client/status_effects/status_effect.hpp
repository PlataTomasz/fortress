#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include "../entities/entity.hpp"
#include <core/string/ustring.h>

/**
 * Stores initial properties of the buff. Most of them are read only.
*/
class StatusEffectData
{
private:

    enum StatusEffectFlags
    {
        IS_DEBUFF = 1,
        IS_DAMAGING = 1 << 1,
        IS_HEALING = 1 << 2,
        IS_CROWD_CONTROL = 1 << 3,
    } uint16_t;

    String name;
    /**
     * Initial max durration of status effect in frames
    */
    int maxDuration;

    StatusEffectData::StatusEffectFlags statusEffectFlags;


public:
    String getName();

    StatusEffectData(const char *_name) : name{_name}
    {

    }
};

class StatusEffect
{
private:
    /**
     * How much frames need to pass before status effect expires?
    */
    int currentDuration;
    int maxDuration;

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

    StatusEffect(StatusEffectData *statusEffectData, float durration, Entity *inflictor);
};

#endif // STATUS_EFFECT_HPP
