#include "disconnect_peer_console_command.h"

#include <server/server.h>

Error DisconnectPeerConsoleCommand::execute(Array args) {
    ERR_FAIL_COND_V((args.size() != 1), Error::ERR_INVALID_PARAMETER);
    ERR_FAIL_COND_V((args[0].get_type() != Variant::INT), Error::ERR_INVALID_PARAMETER);

    //ERR_FAIL_COND_V_MSG((args.size() != 1), Error::ERR_INVALID_PARAMETER, "Command expected 1 argument(s), " + args.size() + " given.");
    //ERR_FAIL_COND_V_MSG((args[0].get_type() != Variant::INT), Error::ERR_INVALID_PARAMETER, "Command expected argument 1 to be Variant::INT, " + args[0].get_type_name() + " given.");
    
    int peer_id = int(args[0]);
    //get_server_instance()->disconnect_peer(peer_id);

    get_server_instance()->disconnect_peer(peer_id);
    print_line("Peer", peer_id, "disconnected from server!");

    return Error::OK;
}