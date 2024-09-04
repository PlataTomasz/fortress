#include "disconnect_from_server_button.h"

#include <client/client.hpp>

void DisconnectFromServerButton::_on_click() {
    Client *client = Client::get_instance();
    ERR_FAIL_NULL(client);

    client->disconnect_from_server();
}

void DisconnectFromServerButton::_init() {    
    connect("pressed", callable_mp(this, &DisconnectFromServerButton::_on_click));
}

void DisconnectFromServerButton::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE: {
			_init();
		} break;

		default:
			break;
	}
}