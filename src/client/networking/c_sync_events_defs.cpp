#include "c_sync_events.h"
#include <client/game.hpp>
#include <core/io/marshalls.h>

void C_EntityPositionSyncEvent::deserialize(uint8_t *ptr, uint64_t size)
{
    Variant::Type expected_types[] = {
        
        
    };

    Variant int_variant;
    Error err = decode_variant(int_variant, ptr, 0);
    ERR_FAIL_COND_MSG(err != OK, "Failed to decode valid data!");
    if(int_variant.get_type() == Variant::INT)
        ent_netid = int_variant;
    else
        ERR_FAIL_MSG("Invalid data type ecountered while deserializing!");
    
    Variant new_position_variant;
    Error err = decode_variant(new_position_variant, ptr, 0);
    ERR_FAIL_COND_MSG(err != OK, "Failed to decode valid data!");
    ERR_FAIL_MSG("Invalid data type ecountered while deserializing!");
    if(new_position_variant.get_type() == Variant::VECTOR3)
        new_position = new_position_variant;
    else
        ERR_FAIL_MSG("Invalid data type ecountered while deserializing!");
}

void C_EntityPositionSyncEvent::execute(Game *Game)
{

}