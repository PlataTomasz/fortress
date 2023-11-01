#if !defined(HELPER_MACROS_INCLUDED)
#define HELPER_MACROS_INCLUDED

#define DISABLE_IN_EDITOR() if(unlikely(Engine::get_singleton()->is_editor_hint())) return;

#define ADD_RPC_CONFIG(method_name, rpc_mode, transfer_mode, channel, call_local) \
    Dictionary method_name ## _rpc_cfg; \
    method_name ## _rpc_cfg["rpc_mode"] = rpc_mode; \
    method_name ## _rpc_cfg["channel"] = channel; \
    method_name ## _rpc_cfg["call_local"] = call_local; \
    method_name ## _rpc_cfg["transfer_mode"] = transfer_mode; \
    rpc_config(#method_name, method_name ## _rpc_cfg); \

#endif // HELPER_MACROS_INCLUDED
