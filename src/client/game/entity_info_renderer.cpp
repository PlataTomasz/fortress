#include "entity_info_renderer.h"

void EntityInfoRenderer::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			_ready();
		} break;

		default:
			break;
	}
}