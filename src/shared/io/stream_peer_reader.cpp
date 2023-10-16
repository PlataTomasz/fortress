#include "stream_peer_reader.h"

StreamPeerReader::StreamPeerReader(const uint8_t *p_data_ptr, uint64_t p_data_size)
{
    data_ptr = p_data_ptr;
    data_size = p_data_size;
}

Error StreamPeerReader::put_data(const uint8_t *p_data, int p_bytes)
{
    ERR_FAIL_MSG("Class can only read data!");
}

Error StreamPeerReader::put_partial_data(const uint8_t *p_data, int p_bytes, int &r_sent)
{
    ERR_FAIL_MSG("Class can only read data!");
}

Error StreamPeerReader::get_data(uint8_t *p_buffer, int p_bytes)
{
    for(int i = 0;i<p_bytes;i++)
    {
        p_buffer[i] = data_ptr[offset+i];
    }
    offset += p_bytes;
	return Error::OK;
}

Error get_partial_data(uint8_t *p_buffer, int p_bytes, int &r_received)
{
    ERR_FAIL_MSG("get_partial_data() is unimplemented for StreamPeerReader!");
}

int StreamPeerReader::get_available_bytes() const
{
    return data_size - offset;
}