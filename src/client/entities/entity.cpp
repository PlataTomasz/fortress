#include "entity.hpp"
#include <scene/3d/area_3d.h>
#include <core/string/string_name.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/primitive_meshes.h>
#include <scene/3d/mesh_instance_3d.h>
#include <core/config/engine.h>
#include <scene/resources/primitive_meshes.h>
#include "../status_effects/status_effect_manager.hpp"
#include <gdextension_helper.hpp>
#include <client/ui/entity_status_bar.hpp>
#include <core/io/resource_loader.h>
#include <scene/resources/packed_scene.h>
#include <scene/resources/box_shape_3d.h>

#include <scene/resources/cylinder_shape_3d.h>



//Entity* Entity::NONE = Entity::create_empty();

Entity::Entity()
{
    DISABLE_IN_EDITOR();
    //TODO: Call virtual initialize(); ?
    connect("ready", callable_mp(this, &Entity::ready));
    connect("ready", callable_mp(this, &Entity::_shared_ready));

    SceneTree::get_singleton()->connect("physics_frame", callable_mp(this, &Entity::physics_frame));
}

Entity::~Entity()
{

}

void Entity::_bind_methods()
{
    //Health changed
    ADD_SIGNAL(MethodInfo("health_change", PropertyInfo(Variant::FLOAT, "value")));
    //Entity will die soon
    ADD_SIGNAL(MethodInfo("pre_death"));
    //Entity died
    ADD_SIGNAL(MethodInfo("on_death"));

    ClassDB::bind_method(D_METHOD("_shared_ready"), &Entity::_shared_ready);

    //ClassDB::bind_method(D_METHOD("onCollision"), &Entity::onCollision);
}

void Entity::ready()
{
    DISABLE_IN_EDITOR();

    //ResourceLoader("res://resources/UI/Game/entity_status_bars/mercenary_status_bar_3d.tscn");
    Ref<PackedScene> scene = ResourceLoader::load("res://resources/UI/Game/entity_status_bars/mercenary_status_bar_3d.tscn");

    EntityStatusBar3D* entity_status_bar = (EntityStatusBar3D*)(*scene)->instantiate();

    add_child(entity_status_bar);
}

void Entity::_shared_ready()
{
    //Load or default
    model = (MeshInstance3D*)get_node(NodePath("Model"));
    if(!model)
    {
        model = memnew(MeshInstance3D);
        model->set_name("Model");
        BoxMesh *mesh = memnew(BoxMesh);
        mesh->set_size(Vector3(0.2f, 0.2f, 0.2f));
        //Does mesh automatically becomes a reference? - Yes, implicit conversion occurs.
        model->set_mesh(mesh);

        add_child(model);
    }
    
    //Replace "Hitbox" node with new
    hitbox = (Area3D*)get_node(NodePath("Hitbox"));
    if(!hitbox)
    {
        //Setting up collisions
        hitbox = memnew(Area3D);
        hitbox->set_name("Hitbox");
        CollisionShape3D* collisionShapeNode = memnew(CollisionShape3D);
        collisionShapeNode->set_name("CollisionShape");

        CylinderShape3D* collisionShape = memnew(CylinderShape3D);

        collisionShape->set_radius(hitbox_radius);

        collisionShapeNode->set_shape(collisionShape);
        hitbox->add_child(collisionShapeNode);

        //Require to make entities collide with eachother
        hitbox->set_monitoring(true);

        add_child(hitbox);
    }
}

void Entity::movement_process_frame()
{
    
}

void Entity::physics_frame()
{
    //StatusEffect handling
    for(auto effect : appliedStatusEffects)
    {
        effect.value->onProcessFrameImpl();
    }
}

bool Entity::removeStatusEffect(String statusEffectName)
{
    return StatusEffectManager::get_singleton()->removeStatusEffect(statusEffectName, this);
}

StatusEffect *Entity::applyStatusEffect(String statusEffectName, float duration, Entity *inflictor)
{
    return StatusEffectManager::get_singleton()->applyStatusEffect(statusEffectName, duration, this, inflictor);
}


bool Entity::hasStatusEffect(String statusEffectName)
{
    if(getStatusEffect(statusEffectName) != nullptr)
        return true;
    else
        return false;
}

StatusEffect *Entity::getStatusEffect(String statusEffectName)
{
    for(auto effect : appliedStatusEffects)
    {
        if(effect.value->name == statusEffectName)
        {
            return effect.value;
        }
    }
    return nullptr;
}

Vector2 Entity::get_facing_direction()
{
    Vector2 result;

    //In Radians - offset to match engine axis
    double angle = this->get_global_rotation().y - M_PI;

    result.x = Math::sin(angle);
    result.y = Math::cos(angle);

    return result;
}

real_t Entity::get_facing_direction_angle()
{
    return this->get_global_rotation_degrees().y;
}

void Entity::take_damage(DamageObject damage_object)
{

    if(stats.health.current > damage_object.value)
    {
        //Damage wont kill that unit
        stats.health.current -= damage_object.value;
        emit_signal(StringName("health_change"), stats.health.current);
        
        //death
    }
    else
    {
        //Damage WILL kill that unit
        print_line("Entity Death!");
        stats.health.current = stats.health.max;

        //emit_signal("pre_death");
        //emit_signal("post_death");
    }
}

/*
Entity* Entity::create_empty()
{
    Entity* ent = new Entity();
    ent->set_name("NONE");

    return ent;
}
*/