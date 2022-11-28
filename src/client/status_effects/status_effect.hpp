#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>

#define VIRTUAL_COPY(DerivedClassName, BaseClassName)               \
public:                                                             \
    BaseClassName* copy()                                           \
    {                                                               \
        return new DerivedClassName(*this);                         \
    }   

#define VIRTUAL_COPY(ClassName)                                     \
public:                                                             \
    ClassName* copy()                                               \
    {                                                               \
        return new ClassName(*this);                                \
    } 

class Entity;

class StatusEffectData
{
protected:


public:
    //Getters/setters




    friend class StatusEffectScript;
    friend class StatusEffectManager;
};

class StatusEffect
{
VIRTUAL_COPY(StatusEffect);

protected:
    String name;
    String friendlyName;
    String tooltip;

    int currStacks;
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
    //Getters/Setters
    void setTarget(Entity* owner);
    Entity* getTarget();

    //TODO: Maybe return value, informing that stack was not added and why?
    void addStacks(int stackCount);

    //Callbacks
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


    void loadData(Dictionary data)
    {
        //TODO: Validate types in json to avoid hard to debug bugs

        name = data.get("name", "none");
        friendlyName = data.get("readableName", name);

        tooltip = data.get("tooltip", "game_tooltip_" + name);


        //If type is invalid 0 is set instead
        maxStacks = int(data.get("maxStacks", 5));
        float secondsDuration = float(data.get("duration", 5));
        //TODO: Get process frames per second from somewhere
        currDuration = 0;
        maxDuration = secondsDuration*60;
    }

    operator String() const;

    StatusEffect(Dictionary data)
    {
        loadData(data);
    };

    friend class Entity;
    friend class StatusEffectManager;
};

#endif // STATUS_EFFECT_HPP
