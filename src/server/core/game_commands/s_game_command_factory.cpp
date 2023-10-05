#include "s_game_command_factory.h"

S_GameCommand *SGameCommandFactory::create(const uint8_t *data, uint64_t size)
{
    uint8_t header = *data;

    //We need to subtract this from size, unless we want to access invalid memory lol
    uint64_t curr_size = 1;

    //Looks messy, but works
    switch (header)
    {
    case SGameCommandType::MOVEMENT:
        {
            return new S_GameCommandMovement(data+size, size-curr_size);
        }
        break;
    
    default:
        print_line("Unknown data received! Discarded.");
        break;
    }

    return nullptr;
}

S_GameCommand *SGameCommandFactory::create(PackedByteArray bytearray)
{
    return SGameCommandFactory::create(bytearray.ptr(), bytearray.size());
}