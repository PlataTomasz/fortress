#if !defined(REQUEST_TYPES_INCLUDED)
#define REQUEST_TYPES_INCLUDED

#include <stdint.h>

namespace Request
{
    enum Type : uint8_t
    {
        UNDEFINED = 0,
        CLIENT_CONNECT,
        MOVEMENT
    };
};

#endif // REQUEST_TYPES_INCLUDED
