#if !defined(SERVER_CONSOLE_COMMAND_INCLUDED)
#define SERVER_CONSOLE_COMMAND_INCLUDED

#include <core/string/ustring.h>
#include <core/templates/vector.h>
#include <core/variant/variant.h>
#include <core/object/object.h>
#include <core/object/class_db.h>

class Server;

class ServerConsoleCommand : public Object {
GDCLASS(ServerConsoleCommand, Object);
private:
    Server *server_instance = nullptr;
public:
    virtual Error execute(Array args = Array()) = 0;

    Server *get_server_instance();

    ServerConsoleCommand(Server *new_server_instance);
};

#endif // SERVER_CONSOLE_COMMAND_INCLUDED
