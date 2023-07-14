#include "tundra_ball.hpp"
#include <scene/resources/primitive_meshes.h>
#include <scene/3d/mesh_instance_3d.h>
#include <core/config/engine.h>
#include <gdextension_helper.hpp>
#include <scene/resources/primitive_meshes.h>

void TundraBall::onCollide(Area3D *collider)
{
    //Deal damage when the ball moved into other entity as a result of other ability or result of displacement toward ball

    /*
    Pseudocode:
    - If collider is under displacement effect or ball final position was result of ability, deal damage to them
    */

}

void TundraBall::_physics_process(double delta)
{
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

void TundraBall::ready()
{
    printf("TundraBall ready!");
    //TODO: Visuals for Entities

    MeshInstance3D *meshInstance = memnew(MeshInstance3D);
    SphereMesh *mesh = memnew(SphereMesh);
    mesh->set_radius(1.5);

    meshInstance->set_mesh(mesh);

    add_child(meshInstance);

    //TODO: Sync with current state of dev/tundra - missing area3d field
    //area3d->connect("area_entered", Callable(this, "onCollide"));
}