#if !defined(DISCONNECT_CONSOLE_COMMAND)
#define DISCONNECT_CONSOLE_COMMAND

#include "server_console_command.h"

class DisconnectPeerConsoleCommand : public ServerConsoleCommand {
GDCLASS(DisconnectPeerConsoleCommand, ServerConsoleCommand);
public:
    virtual Error execute(Array args = Array()) override;

    DisconnectPeerConsoleCommand(Server *new_server_instance) : ServerConsoleCommand(new_server_instance) {};
};

#endif // DISCONNECT_CONSOLE_COMMAND
