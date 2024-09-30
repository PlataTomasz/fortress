#if !defined(REGISTER_SERVERSIDE_TYPES_INCLUDED)
#define REGISTER_SERVERSIDE_TYPES_INCLUDED

#include <server/placeholders/entity_status_bar.h>
#include <server/placeholders/entity_health_bar.h>
#include <server/placeholders/entity_name_display.h>

void register_serverside_types() {
    ClassDB::register_class<EntityStatusBar>();
    ClassDB::register_class<EntityHealthBar>();
    ClassDB::register_class<EntityNameDisplay>();
}

#endif // REGISTER_SERVERSIDE_TYPES_INCLUDED
