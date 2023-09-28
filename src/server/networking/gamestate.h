#if !defined(GAMESTATE_INCLUDED)
#define GAMESTATE_INCLUDED

#include <core/math/vector2.h>
#include <core/string/ustring.h>
#include <core/templates/list.h>
#include <stdint.h>

/**
 * Simplest entities have only their position on map
*/
class EntityDTO 
{
private:
    uint64_t net_id;
    Vector2 position;
    real_t rotation;
public:
    uint64_t get_net_id();

    EntityDTO()
    {

    }
};

class AnimatableEntityDTO : public EntityDTO
{
private:
    struct AnimationState 
    {
        String animation_name;
        real_t time;
    } animation_state;
protected:

public:

};
/**
 * Object that stores all objects that matter for server
*/
class Gamestate
{
private:
    //Frame which the gamestate was tied to
    uint64_t frame = 0;

    List<EntityDTO> entities_state;
public:
    /**
     * Serializes Gamestate to binary data
    */
    uint8_t *to_bytes()
    {
        
    };
};

#endif // GAMESTATE_INCLUDED
