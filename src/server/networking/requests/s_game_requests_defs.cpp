#include "s_game_requests.h"

#include <core/io/stream_peer.h>
#include <core/io/marshalls.h>

void S_MovementGameRequest::execute(S_Game *game)
{
    
}

void S_MovementGameRequest::deserialize(uint8_t *data, uint64_t size)
{
    ERR_FAIL_COND(size < 16);

    int offset = 0;
    //uint64_t - ent_netid
    decode_uint64(data + offset);
    offset+=8;

    //Vector2 - target_position
    decode_float(data + offset);
    offset+=8;
    decode_float(data + offset);
    offset+=8;

};