#if !defined(C_SERVER_REQUESTS)
#define C_SERVER_REQUESTS

#include <core/math/vector2.h>
#include <core/templates/vector.h>

/**
 * Class used to encapsulate data to be sent to server
*/
class C_GameRequest
{
public:
    virtual Vector<uint8_t> serialize() = 0;
};

class C_MovementGameRequest : public C_GameRequest
{
private:
    uint64_t ent_netid;
    Vector2 target_position;
public:
    Vector<uint8_t> serialize() override;
    C_MovementGameRequest(uint64_t p_ent_netid, Vector2 p_target_position);
};

#endif // C_SERVER_REQUESTS
