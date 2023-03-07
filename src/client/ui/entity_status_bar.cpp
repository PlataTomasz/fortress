#include "entity_status_bar.hpp"
#include <gdextension_helper.hpp>

#include <client/entities/entity.hpp>
#include <classes/progress_bar.hpp>
#include <variant/node_path.hpp>

EntityStatusBar3D::EntityStatusBar3D()
{
   
}

void EntityStatusBar3D::_ready()
{
    health_bar = get_node<ProgressBar>("SubViewport/HealthBar");
    ERR_FAIL_COND_MSG(health_bar == nullptr, "HealthBar node is missing!");

    resource_bar = get_node<ProgressBar>("SubViewport/HealthBar");
    ERR_FAIL_COND_MSG(resource_bar == nullptr, "ResourceBar node is missing!");
}

void EntityStatusBar3D::_enter_tree()
{
    Entity* parent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_COND_MSG(parent == nullptr, "Parent is not of type Enity!");

    //Whenever current of maximum health changes
    parent->connect("health_change", Callable(this, "on_health_change"));
    parent->connect("resource_change", Callable(this, "on_resource_change"));
}

void EntityStatusBar3D::on_health_amount_change(float value)
{
    Entity* parent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_COND(parent == nullptr);

    double max_health = parent->stats.health.max;

    if(health_bar)
    {
        health_bar->set_value(value);
        health_bar->set_max(max_health);

        //If health value is 0, play ui animation.
    }
}

void EntityStatusBar3D::on_resource_amount_change(float value)
{
    Entity* parent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_COND(parent == nullptr);

    //FIXME: Resource value change signal is missing
    if(resource_bar)
    {
        resource_bar->set_value(0);
    }
}

void EntityStatusBar3D::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("on_health_amount_change"), &EntityStatusBar3D::on_health_amount_change);
    ClassDB::bind_method(D_METHOD("on_resource_amount_change"), &EntityStatusBar3D::on_resource_amount_change);
}