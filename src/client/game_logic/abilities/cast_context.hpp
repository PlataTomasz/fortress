#if !defined(CAST_CONTEXT_HPP)
#define CAST_CONTEXT_HPP

#include <variant/vector3.hpp>
#include "../../entities/entity.hpp"

/**
 * Class that stores all necessary variables that would be needed to determine things like where projectile needs to go or who is the target of ability and many more.
*/
class CastContext
{
private:
    Entity *caster;
    //World position where the entity should appear
    Vector3 targetPos;
public:
    Entity *getCaster()
    {
        return caster;
    }

    Vector3 getTargetPos()
    {
        return targetPos;
    }

    CastContext(Entity *_caster = nullptr, Vector3 _targetPos = Vector3(0, 0, 0)) : caster{_caster}, targetPos{_targetPos}
    {

    }
};

#endif // CAST_CONTEXT_HPP
