#if !defined(REQUEST_HANDLER_INCLUDED)
#define REQUEST_HANDLER_INCLUDED

#include <stdint.h>

class RequestHandler
{
private:
    static const char *ERROR_MESSAGE_INVALID_SIZE;
public:
    static void handle_request(Ref<ENetPacketPeer> sender, const uint8_t *requst_data, uint64_t size);
};

#endif // REQUEST_HANDLER_INCLUDED
