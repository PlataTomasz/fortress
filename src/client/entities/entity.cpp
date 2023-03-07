#include "entity.hpp"
#include <classes/area3d.hpp>
#include <variant/string_name.hpp>
#include <classes/collision_shape3d.hpp>
#include <classes/box_shape3d.hpp>
#include <classes/mesh_instance3d.hpp>
#include <classes/engine.hpp>
#include <classes/box_mesh.hpp>
#include "../status_effects/status_effect_manager.hpp"
#include <gdextension_helper.hpp>
#include <client/ui/entity_status_bar.hpp>
#include <classes/resource_loader.hpp>
#include <classes/packed_scene.hpp>
#include <variant/string_name.hpp>

using namespace godot;

//Entity* Entity::NONE = Entity::create_empty();

Entity::Entity()
{
    DISABLE_IN_EDITOR();
    connect("ready", Callable(this, "_shared_ready"));
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

void Entity::_ready()
{
    DISABLE_IN_EDITOR();

    //ResourceLoader("res://resources/UI/Game/entity_status_bars/mercenary_status_bar_3d.tscn");
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://resources/UI/Game/entity_status_bars/mercenary_status_bar_3d.tscn");

    EntityStatusBar3D* entity_status_bar = (EntityStatusBar3D*)(*scene)->instantiate();

    add_child(entity_status_bar);
}

void Entity::_shared_ready()
{
    //TODO: Mesh should be loaded from model
    MeshInstance3D *meshInstance = memnew(MeshInstance3D);
    meshInstance->set_name("DEBUG");
    BoxMesh *mesh = memnew(BoxMesh);
    mesh->set_size(Vector3(0.2f, 0.2f, 0.2f));

    meshInstance->set_mesh(mesh);

    //Setting up collisions
    hitbox = memnew(Area3D);
    hitbox->set_name("Hitbox");
    CollisionShape3D *collisionShape3d = memnew(CollisionShape3D);

    BoxShape3D *boxShapePtr = memnew(BoxShape3D);
    boxShapePtr->set_size(Vector3(1.0f, 1.0f, 1.0f));

    Ref<Shape3D> boxShape(boxShapePtr);

    collisionShape3d->set_shape(boxShape);
    hitbox->add_child(collisionShape3d);

    //Require to make entities collide with eachother
    hitbox->set_monitoring(true);
    add_child(hitbox);
    add_child(meshInstance);
    //area3d->connect("area_entered", Callable(this, "onCollision"));
}

void Entity::onCollision(Area3D *collider)
{
    /*
    if(collider)
    {
        if(collider->get_class() != "Entity")
        {
            printf("Collision with: %s", collider->get_name());
            this->queue_free();
        }
    }
    else
        printf("Invalid collider!\n");
    */
}

//
void Entity::movementProcess()
{

}

void Entity::_physics_process(double delta)
{
    movementProcess();
    currLifetime++;

    if(currLifetime >= maxLifetime)
    {
        //this->queue_free();
    }

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
        UtilityFunctions::print("Entity Death!");
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