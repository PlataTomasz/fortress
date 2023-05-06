#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>
#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <cstdio>



#define VIRTUAL_COPY_STATUS_EFFECT(DerivedClassName, BaseClassName)               \
public:                                                             \
    virtual BaseClassName* copy()                                           \
    {                                                               \
        return new DerivedClassName(*this);                         \
    }   

#define VIRTUAL_COPY(ClassName)                                     \
public:                                                             \
    virtual StatusEffect* copy()                                    \
    {                                                               \
        return new ClassName(*this);                                \
    } 

class Entity;

class StatusEffect
{
VIRTUAL_COPY(StatusEffect);

protected:
    String name;
    String friendly_name;
    String tooltip;

    int curr_stacks;
    int max_stacks;
    /**
    * Max durration of status effect in frames
    */
    int curr_duration;
    int max_duration;

    int damage;

    virtual bool is_permament()
    {
        return false;
    }

    /**
    * Who has the status?
    */
    Entity* target;
    
    /**
     * Who inflicted status?
    */
    Entity* inflictor;
public:
    //Getters/Setters
    void set_target(Entity* owner);
    Entity* get_target();

    int get_current_stacks();


    //TODO: Maybe return value, informing that stack was not added and why?
    void add_stacks(int stack_count = 1);

    //Callbacks
    virtual void on_process_frame_impl() final;

    /**
     * Called when status wears off
    */
    virtual void on_expire(){};
    /**
     * Called when status is applied to entity
    */
    virtual void on_apply()
    {
        printf("StatusEffect::onApply callled!\n");
    };
    /**
     * Called every process frame
    */
    virtual void on_process_frame(){};


    void load_data(Dictionary data)
    {
        //TODO: Validate types in json to avoid hard to debug bugs

        name = data.get("name", "none");
        friendly_name = data.get("readableName", name);

        tooltip = data.get("tooltip", "game_tooltip_" + name);


        //If type is invalid 0 is set instead
        max_stacks = int(data.get("maxStacks", 5));
        float secondsDuration = float(data.get("duration", 5));
        //TODO: Get process frames per second from somewhere
        curr_duration = 0;
        max_duration = secondsDuration*60;
    }

    operator String() const;

    StatusEffect(Dictionary data)
    {
        load_data(data);
    };

    //Should be used only for register purpose
    StatusEffect()
    {

    }

    friend class Entity;
    friend class StatusEffectManager;
};

//TODO: Maybe implement It with Nodes(create StatusEffectInstance class?)
#endif // STATUS_EFFECT_HPP
