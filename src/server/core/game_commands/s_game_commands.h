
#if !defined(GAME_COMMAND_INCLUDED)
#define GAME_COMMAND_INCLUDED

#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <core/io/marshalls.h>

class Player;
class S_Game;

#define S_GAME_COMMAND_METHODS(classname) \
public:\
    void execute(S_Game *game) override; \
    PackedByteArray serialize() override;\
    void deserialize(const uint8_t *data, uint64_t size) override;\
    bool is_size_valid(uint64_t size);\
    classname(const uint8_t *data, uint64_t size) : S_GameCommand(data, size) {}\
    classname(PackedByteArray bytearray) : S_GameCommand(bytearray) {}\
    ~classname(){}
    

/**
 * Class responsible for holding data regarding different game events, serialization, deserialization and validation in preparation to be sent to/received from server
*/
class S_GameCommand
{
public:
    
private:
    //Player that sent GameCommand
    Player *sender;
protected:

public:

    virtual PackedByteArray serialize() = 0;
    //Checks if size of the data buffer matches expected size
    virtual bool is_size_valid(uint64_t size) = 0;
    virtual void execute(S_Game *game);
    virtual void deserialize(const uint8_t *data, uint64_t size){};

    S_GameCommand(PackedByteArray bytearray)
    {
        deserialize(bytearray.ptr(), bytearray.size());
    }

    S_GameCommand(const uint8_t *data, uint64_t size)
    {
        deserialize(data, size);
    }
};

class S_GameCommandMovement : public S_GameCommand
{
private:
    Vector2 new_position;
public:
    S_GAME_COMMAND_METHODS(S_GameCommandMovement);
};

#endif // GAME_COMMAND_INCLUDED