#include "c_game_command_factory.h"

C_GameCommand *C_GameCommandFactory::create(const uint8_t *data, uint64_t size)
{
    uint8_t header = *data;
    const uint8_t *ptr = data;
    uint64_t offseted_size = size - 1;

    switch (header)
    {
    case C_GameCommandType::MOVEMENT:
        {
            return new C_GameCommandMovement(ptr, offseted_size);
        }
        break;
    
    default:
        break;
    }
}

C_GameCommand *C_GameCommandFactory::create(PackedByteArray data)
{
    return C_GameCommandFactory::create(data.ptr(), data.size());
}