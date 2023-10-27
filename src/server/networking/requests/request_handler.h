#if !defined(REQUEST_HANDLER_INCLUDED)
#define REQUEST_HANDLER_INCLUDED

#include <stdint.h>
#include <scene/main/node.h>

class RequestHandler : public Node
{
GDCLASS(RequestHandler, Node);
protected:
    static void _bind_methods();
public:
    //RPC methods
    void movement_request(Vector2 target_position);

    RequestHandler();
};

#endif // REQUEST_HANDLER_INCLUDED
