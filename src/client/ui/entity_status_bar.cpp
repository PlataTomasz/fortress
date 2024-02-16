#include "entity_status_bar.hpp"
#include <gdextension_helper.hpp>

#include <shared/entities/entity.h>
#include <scene/gui/progress_bar.h>
#include <core/string/node_path.h>

EntityStatusBar3D::EntityStatusBar3D()
{
    connect("ready", callable_mp(this, &EntityStatusBar3D::ready));
    connect("tree_entered", callable_mp(this, &EntityStatusBar3D::tree_entered));
}

void EntityStatusBar3D::ready()
{
    health_bar = (ProgressBar*)get_node(NodePath("SubViewport/HealthBar"));
    ERR_FAIL_COND_MSG(health_bar == nullptr, "HealthBar node is missing!");

    resource_bar = (ProgressBar*)get_node(NodePath("SubViewport/HealthBar"));
    ERR_FAIL_COND_MSG(resource_bar == nullptr, "ResourceBar node is missing!");

    Entity* parent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_COND_MSG(parent == nullptr, "Parent is not of type Enity!");

    on_health_change();
    //health_bar->set_max(parent->stats.health.get_current_value());
    //health_bar->set_value(parent->stats.health.get_max_health_stat().get_final_value());
}

void EntityStatusBar3D::tree_entered()
{
    //Whenever current of maximum health changes
    get_parent()->connect("health_change", callable_mp(this, &EntityStatusBar3D::on_health_change));
    get_parent()->connect("resource_change", Callable(this, "on_resource_change"));
}

void EntityStatusBar3D::on_health_change()
{
    Entity* parent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_COND(parent == nullptr);

    double value = parent->stats.health.get_current_value();

    double max_health = parent->stats.health.get_max_health_stat();

    if(health_bar)
    {
        health_bar->set_max(max_health);
        health_bar->set_value(value);
        //If health value is 0, play ui animation.
    }
}

void EntityStatusBar3D::on_resource_change(float value)
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
    ClassDB::bind_method(D_METHOD("on_health_change"), &EntityStatusBar3D::on_health_change);
}