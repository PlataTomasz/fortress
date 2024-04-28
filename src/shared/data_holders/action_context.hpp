#if !defined(action_context_HPP_INCLUDED)
#define action_context_HPP_INCLUDED

#include <core/math/vector3.h>
#include <shared/entities/entity.h>

class Entity;

/**
 * Class that stores all necessary variables that would be needed to determine things like where projectile needs to go or who is the target of ability and many more.
*/
class ActionContext : public RefCounted
{
GDCLASS(ActionContext, RefCounted);
private:
    //TODO: Add sane default
    Entity *user = nullptr;
    Vector3 use_position;

    Vector3 target_position;
    Entity *target_entity = nullptr;

public:
    Entity* get_user()
    {
        return user;
    }

    Vector3 get_target_position()
    {
        return target_position;
    }

    Entity* get_target_entity()
    {
        return target_entity;
    }
    
    ActionContext(
        Entity* _user,
        Vector3 _use_position,
        Vector3 _target_position,
        Entity* _target_entity 
    ) :
        user{_user},
        use_position{_use_position},
        target_position{_target_position},
        target_entity{_target_entity}
    {
        
    }

    ActionContext(ActionContext& action_context)
    {
        this->user = action_context.user;
        this->use_position = action_context.use_position;
        this->target_position = action_context.target_position;
        this->target_entity = action_context.target_entity;
    }
};

#endif // action_context_HPP_INCLUDED
