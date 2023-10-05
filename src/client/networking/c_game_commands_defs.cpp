#include "c_game_commands.h"
#include <core/string/print_string.h>

//Serialize method is pointless because that object is used only to parse game command from server
PackedByteArray C_GameCommandMovement::serialize()
{
    
}

bool C_GameCommandMovement::is_size_valid(uint64_t size)
{
    return true;
}

void C_GameCommandMovement::execute(Game *game)
{
    print_line("Server issued ent_netid: ", ent_netid, "to move to", new_position);
}

void C_GameCommandMovement::deserialize(const uint8_t *data, uint64_t size)
{

    const uint64_t *ent_netid_ptr = reinterpret_cast<const uint64_t*>(data);
    ent_netid = *ent_netid_ptr++;
    
    const real_t *x_ptr = reinterpret_cast<const real_t*>(ent_netid);
    x_ptr++;

    const real_t *y_ptr = reinterpret_cast<const real_t*>(x_ptr);
    y_ptr++;

    new_position = Vector2(
        *x_ptr,
        *y_ptr
    );
}

C_GameCommandMovement::C_GameCommandMovement(uint64_t ent_netid, Vector2 target_pos)
{
    
}