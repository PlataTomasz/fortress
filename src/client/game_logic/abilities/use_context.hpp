#if !defined(USE_CONTEXT_HPP_INCLUDED)
#define USE_CONTEXT_HPP_INCLUDED

#include <core/math/vector3.h>
#include <client/entities/entity.hpp>

/**
 * Class that stores all necessary variables that would be needed to determine things like where projectile needs to go or who is the target of ability and many more.
*/
class UseContext
{
private:
    //TODO: Add sane default
    Entity* user;
    Vector3 use_position;

    Vector<Vector3> target_positions;

    Vector<Entity*> target_entities;

public:
    Entity* get_user()
    {
        return user;
    }

    Vector3 get_target_position()
    {
        return target_positions[0];
    }

    Entity* get_target_entity()
    {
        return target_entities[0];
    }

    const Vector<Vector3>& get_target_positions()
    {
        return target_positions;
    }
    
    UseContext(
        Entity* _user,
        Vector3 _use_position,
        Vector<Vector3> _target_positions,
        Vector<Entity*> _target_entities 
    ) :
        user{_user},
        use_position{_use_position},
        target_entities{_target_entities},
        target_positions{_target_positions}
    {
        
    }

    UseContext(UseContext& use_context)
    {
        this->user = use_context.user;
        this->use_position = use_context.use_position;
        this->target_positions = use_context.target_positions;
        this->target_entities = use_context.target_entities;
    }
};

#endif // USE_CONTEXT_HPP_INCLUDED
