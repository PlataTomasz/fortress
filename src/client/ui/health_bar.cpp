#include "health_bar.hpp"
#include <client/entities/entity.hpp>
#include <scene/main/viewport.h>
#include <scene/3d/camera_3d.h>

void EntityHealthBar::_bind_methods()
{

}

void EntityHealthBar::_ready()
{
    //Mapping values from entity
    Entity* ent = (Entity*)get_parent();

    set_max(ent->stats.health.get_max_health_stat());
    set_value(ent->stats.health.get_current_value());
}

void EntityHealthBar::update_value(float new_health)
{
    Entity* ent = (Entity*)get_parent();

    double curr_hp_percentage = new_health/ent->stats.health.get_max_health_stat();

    this->set_value(curr_hp_percentage);
}

/**
 * When healthbar owner changes position
*/
void EntityHealthBar::update_position(Vector2 new_pos)
{
    this->set_position(new_pos);
}
