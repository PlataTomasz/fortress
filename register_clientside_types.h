#if !defined(REGISTER_CLIENTSIDE_TYPES_INCLUDED)
#define REGISTER_CLIENTSIDE_TYPES_INCLUDED

#include <client/ui/buttons/disconnect_from_server_button.h>

void register_clientside_types() {
    ClassDB::register_class<DisconnectFromServerButton>();
}

#endif // REGISTER_CLIENTSIDE_TYPES_INCLUDED
