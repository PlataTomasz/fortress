#include "tundra_ball.hpp"
#include <classes/box_shape3d.hpp>
#include <classes/mesh_instance3d.hpp>
#include <classes/engine.hpp>
#include <gdextension_helper.hpp>
#include <classes/sphere_mesh.hpp>

TundraBall::TundraBall(Entity *owner)
{
    if(!Engine::get_singleton()->is_editor_hint())
    {
        this->owner = owner;
        this->maxRangeFromOwner = 0.8;
        //TODO: Find alternative for callable_mp
        //connect("ready", callable_mp(this, &TundraBall::onReady));
        //area3d->connect("area_entered", callable_mp(this, &TundraBall::onCollision));
    }
}

void TundraBall::onCollision(Area3D *collider)
{
    //Deal damage when the ball moved into other entity as a result of other ability or result of displacement toward ball

    /*
    Pseudocode:
    - If collider is under displacement effect or ball final position was result of ability, deal damage to them
    */

}

void TundraBall::onPhysicsFrame()
{
    //Get delta
    //FIXME: Delta is invalid
    double delta = 0;

    //Get owner position and move toward him if It's too far away
    Vector3 ballPos = this->get_position();
    if(ballPos.distance_to(owner->get_position()) > maxRangeFromOwner)
    {
        Vector3 lerpResult = this->get_position().lerp(owner->get_position(), delta);

        printf("lerpResult: %s\n", String(lerpResult).ascii().get_data());

        this->set_position(lerpResult);

        //TODO: Prevent position updates if Tundra is currently casting ability
        //if(owner.isCurrentlyCastingAbility)?
        //Signal position change and tie ball position update to owner position changes?

    }
}

void TundraBall::onReady()
{
    printf("TundraBall ready!");
    //TODO: Visuals for Entities

    MeshInstance3D *meshInstance = memnew(MeshInstance3D);
    SphereMesh *mesh = memnew(SphereMesh);
    mesh->set_radius(1.5);

    meshInstance->set_mesh(mesh);

    add_child(meshInstance);
    //TODO: Find alternative for callable_mp
    //get_tree()->connect("physics_frame", callable_mp(this, &TundraBall::onPhysicsFrame));
}