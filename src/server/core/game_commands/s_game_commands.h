
#if !defined(GAME_COMMAND_INCLUDED)
#define GAME_COMMAND_INCLUDED

#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <core/io/marshalls.h>

class Player;
class S_LivingEntity;
class S_BaseEntity;
class S_Game;

/**
 * Class responsible for holding data regarding different game events, serialization, deserialization and validation in preparation to be sent to/received from server
*/
class S_GameCommand
{
public:
    
private:
protected:

public:
    virtual void execute(S_Game *game) = 0;

    S_GameCommand(){};
    virtual ~S_GameCommand(){};
};

class S_GameCommandMovement : public S_GameCommand
{
private:
    S_BaseEntity *issuer = nullptr;
    S_LivingEntity *ent = nullptr;
    Vector2 new_position;
public:
    virtual void execute(S_Game *game) override;

    S_GameCommandMovement(S_BaseEntity *p_issuer, S_LivingEntity *p_ent, Vector2 p_new_position);
};

#endif // GAME_COMMAND_INCLUDED