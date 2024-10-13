#if !defined(RPC_CONFIG_BUILDER_INCLUDED)
#define RPC_CONFIG_BUILDER_INCLUDED

#include <scene/main/multiplayer_api.h>

class RPCConfigBuilder {
private:
    MultiplayerPeer::TransferMode _transfer_mode = MultiplayerPeer::TransferMode::TRANSFER_MODE_RELIABLE;
    MultiplayerAPI::RPCMode _rpc_mode = MultiplayerAPI::RPCMode::RPC_MODE_ANY_PEER;
    int _channel = 0;
    bool _call_local = false;
public:
    RPCConfigBuilder &transfer_mode(MultiplayerPeer::TransferMode new_transfer_mode) {
        _transfer_mode = new_transfer_mode;
        return *this;
    }

    RPCConfigBuilder &rpc_mode(MultiplayerAPI::RPCMode new_rpc_mode) {
        _rpc_mode = new_rpc_mode;
        return *this;
    }

    RPCConfigBuilder &channel(int new_channel) {
        _channel = new_channel;
        return *this;
    }

    RPCConfigBuilder &call_local(bool new_call_local) {
        _call_local = new_call_local;
        return *this;
    }

    Dictionary build() {
        Dictionary rpc_config;
        rpc_config["rpc_mode"] = _rpc_mode;
        rpc_config["channel"] = _channel;
        rpc_config["call_local"] = _call_local;
        rpc_config["transfer_mode"] = _transfer_mode;
        return rpc_config;
    }
};

#endif // RPC_CONFIG_BUILDER_INCLUDED
