#if !defined(USE_CONTEXT_HPP_INCLUDED)
#define USE_CONTEXT_HPP_INCLUDED

#include <core/math/vector3.h>
#include <shared/entities/entity.h>

class AbilityCasterComponent;

/**
 * Class that stores all necessary variables that would be needed to determine things like where projectile needs to go or who is the target of ability and many more.
*/
class UseContext : public RefCounted
{
GDCLASS(UseContext, RefCounted);
private:
    //TODO: Add sane default
    AbilityCasterComponent *user = nullptr;
    Vector3 use_position;

    Vector3 target_position;
    Entity *target_entity = nullptr;

public:
    AbilityCasterComponent* get_user()
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
    
    UseContext(
        AbilityCasterComponent* _user,
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

    UseContext(UseContext& use_context)
    {
        this->user = use_context.user;
        this->use_position = use_context.use_position;
        this->target_position = use_context.target_position;
        this->target_entity = use_context.target_entity;
    }
};

#endif // USE_CONTEXT_HPP_INCLUDED
