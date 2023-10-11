#include "c_game_requests.h"
#include <core/io/stream_peer.h>
#include <core/io/marshalls.h>

Vector<uint8_t> C_MovementGameRequest::serialize()
{
    StreamPeerBuffer buffer;
    buffer.resize(16);

    buffer.put_u64(ent_netid);
    buffer.put_float(target_position.x);
    buffer.put_float(target_position.y);

    return buffer.get_data_array();
}

C_MovementGameRequest::C_MovementGameRequest(uint64_t p_ent_netid, Vector2 p_target_position)
{
    ent_netid = p_ent_netid;
    target_position = p_target_position;
}