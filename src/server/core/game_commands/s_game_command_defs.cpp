#include "s_game_commands.h"
#include <server/core/s_game.h>

//Movement request from player
void S_GameCommandMovement::execute(S_Game *game)
{
    print_line("Player", "[1]", "wants to move to", new_position, "from", "[old_position]");
    //Movement code here
}

PackedByteArray S_GameCommandMovement::serialize()
{
    PackedByteArray bytearray;

    bytearray.resize(2*sizeof(real_t));
    bytearray.append(new_position.x);
    bytearray.append(new_position.y);

    return bytearray;
}

void S_GameCommandMovement::deserialize(const uint8_t *data, uint64_t size)
{
    real_t x = *reinterpret_cast<const real_t*>(data);
    real_t y = *reinterpret_cast<const real_t*>(data + sizeof(real_t));

    new_position = Vector2(x, y);
}

bool S_GameCommandMovement::is_size_valid(uint64_t size)
{
    //1x Vector2 = 2x real_t
    constexpr uint64_t expected_size = 2*sizeof(real_t);
    return expected_size == size;
}

