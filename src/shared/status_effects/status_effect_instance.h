#if !defined(STATUS_EFFECT_INSTANCE_INCLUDED)
#define STATUS_EFFECT_INSTANCE_INCLUDED

#include <scene/main/node.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>

//Instance of status effect created from resource
class StatusEffectInstance : public Node
{
protected:
    //Stores StatusEffect object that was used to create that StatusEffectInstance
    StatusEffect *created_from;

    //What has that status effect?
    ObjectPtr<Entity> victim = nullptr;
    //What inflicted this status effect?
    ObjectPtr<Entity> inflictor = nullptr;

    float max_duration = 3.0f;
    float elapsed_duration = 0.0f;

    int max_stacks = 1;
    int current_stacks = 1;

    virtual void _tick_impl()
    {

    }

    void _tick()
    {
        // Code called every frame
        float delta = SceneTree::get_singleton()->get_physics_process_time();


        if(max_duration != -1 || max_duration > elapsed_duration)
        {
            //Call StatusEffect per tick method
            _tick_impl();
        }
        else
        {
            //My time has come - Bye Bye
            expire(); //Might cause double free in the future
        }
    }
    

public:
    int get_current_stacks()
    {
        return current_stacks;
    }

    void add_stacks(int stack_count, bool should_renew)
    {
        this->current_stacks = this->current_stacks + stack_count;
        
        if(should_renew)
        {
            elapsed_duration = 0;
        }
    }

    ObjectPtr<Entity> get_victim()
    {
        return victim;
    }

    void set_victim(ObjectPtr<Entity> new_victim)
    {
        //TODO: Implement a way to move StatusEffect to other entity
        //Disallow change of owner if it was already set
        /*
        if(this->target == nullptr)
        {
            this->target = target;
        }
        */
        this->victim = new_victim;
    }

    void set_elapsed_duration(float p_elapsed_duration)
    {

    }

    void set_max_duration(float p_max_duration)
    {

    }

    //Forces status effect to finish, causing it to be removed in the next frame
    void expire()
    {
        //Emit signals here
        expire_silent();
    }

    //Same as StatusEffectInstance::expire(), but doesn't trigger on_expire effects
    void expire_silent()
    {
        set_physics_process(false);
        queue_free();
    }
};

#endif // STATUS_EFFECT_INSTANCE_INCLUDED
