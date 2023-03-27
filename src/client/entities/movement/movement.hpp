#if !defined(BASIC_MOVEMENT_HPP)
#define BASIC_MOVEMENT_HPP

#include <godot_cpp/core/math/vector3.h>



class Movement
{
public:
    /**
     * Returns next position where entity should be placed in. Usually based on current position.
    */
    virtual Vector3 getNextPos() = 0;
};

#endif // BASIC_MOVEMENT_HPP
