#if !defined(RPC_REGISTERER_INCLUDED)
#define RPC_REGISTERER_INCLUDED

#include <scene/main/node.h>

class RPCRegisterer {
public:
    RPCRegisterer(Node *node, const String &method_name, Dictionary rpc_config) {
        node->rpc_config(method_name, rpc_config);
    }
};

#endif // RPC_REGISTERER_INCLUDED
