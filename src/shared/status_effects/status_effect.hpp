#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>
#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <cstdio>

class Entity;

//Class which acts as a template for instantiating new status effect instances
//NOTE: Name is set by StatusEffectManager
class StatusEffect : public Resource
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
    StringName instantiate_classname;
    //1 means that StatusEffect is unstackable
    float max_stacks = 1;
    float max_duration;

    //Additional data - for instancing purposes
    Dictionary data;

    int max_stacks;

    //Permament effects are those which max_duration is -1. That also includes effect that expire under certain conditions(like leaving slowing area)
    virtual bool is_permament()
    {
        return false;
    }
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

    //Creates instance of status effect based on this status effect
    StatusEffectInstance *create_instance()
    {
        //NOTE: Currently doesn't support external classes(ex. GDScript)
        StatusEffectInstance *status_effect_instance = Object::cast_to<StatusEffectInstance>(ClassDB::instantiate(instantiate_classname));

        if(!status_effect_instance)
            print_error("No such class! Instantiation of" + instantiate_classname + "failed! Returning nullptr!");

        return status_effect_instance;
    }

    operator String() const;

    //WARN: DO NOT USE !!! Should be used only for engine register purpose.
    //NOTE: Maybe just make this class abstract and instantiable only by StatusEffectManager?
    StatusEffect()
    {
        
    }

    void initialize_generic_fields(Dictionary data)
    {
        //FIXME: Dictionary currently stores duplicates of fields
        //TODO: Validate data stored in Dictionary

        Variant classname_var = data.get_valid("classname");
        //SEI is acronym for StatusEffectInstance. SEI contains logic and variables for quick accesss for status effect instances
        instantiate_classname = classname_var.get_type() == Variant::Type::STRING ? String(classname_var) : get_name().capitalize().replace(" ", "") + "SEI";

        Variant type_var = data.get_valid("type");
        if(type_var.get_type() == Variant::Type::INT)
        {
            int type_num = type_var.operator signed int();
            if(type_num >= 0 && type_num < StatusEffect::Type::TYPE_MAX)
            {
                type = (StatusEffect::Type)type_num;
            }
            else
            {
                type = StatusEffect::Type::MISC;
            }
        }
        else
        {
            type = StatusEffect::Type::MISC;
        }

    }

    StatusEffect(String new_name)
    {
        set_name(new_name);
    }

    friend class Entity;
    friend class StatusEffectManager;
};

//TODO: Maybe implement It with Nodes(create StatusEffectInstance class?)
#endif // STATUS_EFFECT_HPP
