#include "entity.h"

#include <server/server.h>
#include <server/core/game.h>

void Entity::add_networked_property(StringName property_name)
{
    Server::get_game()->add_node_networked_property(this, property_name);
}