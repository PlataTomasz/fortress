#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>
#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <cstdio>
#include <scene/main/node.h>

class Entity;

//Class which acts as a template for instantiating new status effect instances
//NOTE: Name is set by StatusEffectManager
class StatusEffect : public Node
{
public:
    enum Type
    {
        MISC,
        BUFF,
        DEBUFF,
        TYPE_MAX
    };
protected:
    //Generic fields - every status event have them
    StatusEffect::Type type = StatusEffect::Type::MISC;
    //1 means that StatusEffect is unstackable
    int max_stacks = 1;
    float max_duration = 3;

    int current_stacks = 1;
    float current_duration = 0;

    //Permament effects are those which max_duration is -1. That also includes effect that expire under certain conditions(like leaving slowing area)
    virtual bool is_permament()
    {
        return false;
    }
public:
    Entity *get_target();

    int get_current_stacks();


    //TODO: Maybe return value, informing that stack was not added and why?
    void add_stacks(int stack_count = 1, bool refresh = true);

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
    virtual void _tick(){};

    operator String() const;

    //WARN: DO NOT USE !!! Should be used only for engine register purpose.
    //NOTE: Maybe just make this class abstract and instantiable only by StatusEffectManager?
    StatusEffect()
    {
        
    }

    friend class Entity;
    friend class StatusEffectManager;
};

//TODO: Maybe implement It with Nodes(create StatusEffectInstance class?)
#endif // STATUS_EFFECT_HPP
