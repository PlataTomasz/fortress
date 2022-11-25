#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>

class Entity;

class StatusEffectData
{
protected:
    String name;
    String friendlyName;
    String tooltip;

    int maxStacks;
    /**
    * Max durration of status effect in frames
    */
    int currDuration;
    int maxDuration;

    int damage;

    /**
    * Who has the status?
    */
    Entity *target;
    
    /**
     * Who inflicted status?
    */
    Entity *inflictor;

public:
    //Getters/setters
    void setTarget(Entity* owner);
    Entity* getTarget();

    operator String() const;

    StatusEffectData(
        String _name,
        String _friendlyName,
        String _tooltip,
        int _maxStacks,
        int _maxDuration,
        int _damage,
        Entity *_target = nullptr,
        Entity *_inflictor = nullptr
    ) : 
        name{_name},
        friendlyName{_friendlyName},
        tooltip{_tooltip},
        maxStacks{_maxStacks},
        maxDuration{_maxDuration},
        damage{_damage},
        target{_target},
        inflictor{_inflictor}
    {};

    /**
     * Returns StatusEffectData pointer as T class pointer. Returns nullptr if conversion failed - Most likely non child class of StatusEffectData.
    */
    template<class T>
    T* get()
    {
        return dynamic_cast<T*>(this)
    }

    friend class StatusEffectScript;
    friend class StatusEffectManager;
};

class StatusEffectScript
{
protected:
    StatusEffectData *statusEffectData;
public:
    virtual void onProcessFrameImpl() final;

    /**
     * Called when status wears off
    */
    virtual void onExpire(){};
    /**
     * Called when status is applied to entity
    */
    virtual void onApply(){};
    /**
     * Called every process frame
    */
    virtual void onProcessFrame(){};

    friend class StatusEffectManager;
};

class StatusEffect
{
protected:
    StatusEffectData *statusEffectData;
    StatusEffectScript *statusEffectScript;

public:
    StatusEffect(StatusEffectData *_statusEffectData, StatusEffectScript *_statusEffectScript) : statusEffectData{_statusEffectData}, statusEffectScript{_statusEffectScript}{};

    /**
     * Returns field statusEffectData converted to type T.
    */
    template<class T = StatusEffect>
    T *getStatusEffectData()
    {
        return dynamic_cast<T*>(this);
    }

    //operator String() const;

    friend class Entity;
    friend class StatusEffectManager;
};

#endif // STATUS_EFFECT_HPP
