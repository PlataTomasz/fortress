#if !defined(STREAM_PEER_READER_INCLUDED)
#define STREAM_PEER_READER_INCLUDED

#include <core/io/stream_peer.h>

class StreamPeerReader : public StreamPeer
{
GDCLASS(StreamPeerReader, StreamPeer);

private:
    const uint8_t *data_ptr;
    uint64_t data_size;
    int offset = 0;

public:
    virtual Error put_data(const uint8_t *p_data, int p_bytes) override;
	virtual Error put_partial_data(const uint8_t *p_data, int p_bytes, int &r_sent) override;

    virtual Error get_data(uint8_t *p_buffer, int p_bytes) override;
    virtual Error get_partial_data(uint8_t *p_buffer, int p_bytes, int &r_received) override;

    virtual int get_available_bytes() const override;

    StreamPeerReader(const uint8_t *p_data_ptr, uint64_t p_data_size);
};

#endif // STREAM_PEER_READER_INCLUDED
