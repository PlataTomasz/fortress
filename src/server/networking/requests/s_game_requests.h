#if !defined(GAME_REQUESTS_INCLUDED)
#define GAME_REQUESTS_INCLUDED

#include <stdint.h>
#include <core/templates/vector.h>
#include <core/math/vector2.h>

class S_Game;

//TODO: Implement byte data size check
class S_GameRequest
{
protected:
    S_GameRequest(){};
public:
    virtual void execute(S_Game *game) = 0;
    virtual void deserialize(uint8_t *data, uint64_t size) = 0;
    S_GameRequest(uint8_t *data, uint64_t size)
    {
        deserialize(data, size);
    }
};

class S_MovementGameRequest : public S_GameRequest
{
private:
    uint64_t ent_netid;
    Vector2 target_position;
public:
    void execute(S_Game *game) override;
    void deserialize(uint8_t *data, uint64_t size) override;

    S_MovementGameRequest(uint8_t *data, uint64_t size) : S_GameRequest(data, size){};
};

#endif // GAME_REQUESTS_INCLUDED
