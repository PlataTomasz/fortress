#include "health_bar.hpp"
#include <client/entities/entity.hpp>
#include <scene/main/viewport.h>
#include <scene/3d/camera_3d.h>

void EntityHealthBar::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("update_value"), &EntityHealthBar::update_value);
}

void EntityHealthBar::_ready()
{

    //Mapping values from entity
    Entity* ent = (Entity*)get_parent();

    double curr_hp_percentage = ent->stats.health.current/ent->stats.health.max;
    ent->connect("health_change", Callable(this, "update_value"));

    set_value(curr_hp_percentage);

    Vector2 bar_pos = get_viewport()->get_camera_3d()->unproject_position(ent->get_global_position()) - Vector2(80, 128);
}

void EntityHealthBar::update_value(float new_health)
{
    Entity* ent = (Entity*)get_parent();

    double curr_hp_percentage = new_health/ent->stats.health.max;

    this->set_value(curr_hp_percentage);
}

/**
 * When healthbar owner changes position
*/
void EntityHealthBar::update_position(Vector2 new_pos)
{
    this->set_position(new_pos);
}
