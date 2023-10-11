#if !defined(C_GAME_COMAMNDS_INCLUDED)
#define C_GAME_COMAMNDS_INCLUDED

#include <core/variant/variant.h>

class Game;

#define C_GAME_COMMAND_METHODS(classname) \
public:\
    void execute(Game *game) override; \
    PackedByteArray serialize() override;\
    void deserialize(const uint8_t *data, uint64_t size) override;\
    bool is_size_valid(uint64_t size);\
    classname(const uint8_t *data, uint64_t size) : C_GameCommand(data, size) {}\
    ~classname(){}

class C_GameCommand
{
public:
    
private:
    
protected:

public:
    virtual PackedByteArray serialize() = 0;
    //Checks if size of the data buffer matches expected size
    virtual bool is_size_valid(uint64_t size) = 0;
    virtual void execute(Game *game) = 0;
    virtual void deserialize(const uint8_t *data, uint64_t size){};

    C_GameCommand(const uint8_t *data, uint64_t size)
    {
        deserialize(data, size);
    }
};

class C_GameCommandMovement : public C_GameCommand
{
C_GAME_COMMAND_METHODS(C_GameCommandMovement);
private:
    uint64_t ent_netid;
    Vector2 new_position;
protected:

public:
    C_GameCommandMovement();
};

#endif // C_GAME_COMAMNDS_INCLUDED
