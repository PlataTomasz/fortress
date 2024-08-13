#include "server_console_command.h"

#include <server/server.h>

ServerConsoleCommand::ServerConsoleCommand(Server *new_server_instance) {
    server_instance = new_server_instance;
}

Server *ServerConsoleCommand::get_server_instance() {
    return server_instance;
}