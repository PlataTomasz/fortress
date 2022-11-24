#include "entity.hpp"
#include <scene/3d/area_3d.h>
#include <core/string/string_name.h>
#include <scene/scene_string_names.h>
#include <scene/3d/collision_shape_3d.h> 
#include <scene/resources/box_shape_3d.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>
#include "../status_effects/status_effect_manager.hpp"


Entity::Entity()
{
    if(!Engine::get_singleton()->is_editor_hint())
    {
        set_physics_process(true);

        connect("ready", callable_mp(this, &Entity::onReady));
    }
}

Entity::~Entity()
{

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
    area3d->connect("area_entered", callable_mp(this, &Entity::onCollision));

    get_tree()->connect("physics_frame", callable_mp(this, &Entity::onPhysicsFrame));
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
    for(auto effect : statusEffects)
    {
        effect.value->statusEffectScript->onProcessFrameImpl();
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
    //Check if status effect is registered
    if(statusEffects.find(statusEffectName) != statusEffects.end())
        return true;
    else
        return false;
}