#include "entity.hpp"
#include <classes/area3d.hpp>
#include <variant/string_name.hpp>
#include <classes/collision_shape3d.hpp>
#include <classes/box_shape3d.hpp>
#include <classes/mesh_instance3d.hpp>
#include <classes/engine.hpp>
#include <classes/box_mesh.hpp>
#include "../status_effects/status_effect_manager.hpp"

using namespace godot;

Entity::Entity()
{
    if(!Engine::get_singleton()->is_editor_hint())
    {
        set_physics_process(true);

        //TODO: Find alternative for callable_mp
        //connect("ready", callable_mp(this, &Entity::onReady));
    }
}

Entity::~Entity()
{

}

void Entity::_bind_methods()
{
    ADD_SIGNAL(MethodInfo("health_lost", PropertyInfo(Variant::FLOAT, "value")));
    ADD_SIGNAL(MethodInfo("health_recover", PropertyInfo(Variant::FLOAT, "value")));
}

void Entity::onReady()
{

    //TODO: Mesh should be loaded from model
    MeshInstance3D *meshInstance = memnew(MeshInstance3D);
    BoxMesh *mesh = memnew(BoxMesh);

    meshInstance->set_mesh(mesh);

    //Setting up collisions
    Area3D *area3d = memnew(Area3D);
    CollisionShape3D *collisionShape3d = memnew(CollisionShape3D);

    BoxShape3D *boxShapePtr = memnew(BoxShape3D);
    boxShapePtr->set_size(Vector3(0.1f, 0.1f, 0.1f));

    Ref<Shape3D> boxShape(boxShapePtr);

    collisionShape3d->set_shape(boxShape);
    area3d->add_child(collisionShape3d);

    //Require to make entities collide with eachother
    area3d->set_monitoring(true);
    add_child(area3d);
    add_child(meshInstance);
    //TODO: Find alternative for callable_mp
    //area3d->connect("area_entered", callable_mp(this, &Entity::onCollision));
    //get_tree()->connect("physics_frame", callable_mp(this, &Entity::onPhysicsFrame));
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

void Entity::onPhysicsFrame()
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
        effect->onProcessFrameImpl();
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
        if(effect->name == statusEffectName)
        {
            return effect;
        }
    }
    return nullptr;
}