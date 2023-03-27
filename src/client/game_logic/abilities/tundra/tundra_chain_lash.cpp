#include "tundra_chain_lash.hpp"

#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/primitive_meshes.h>
#include <scene/3d/area_3d.h>
#include <core/object/object.h>
#include <scene/resources/box_shape_3d.h>
#include "../../../entities/mercenaries/tundra/tundra_ball.hpp"

void TundraChainLashAbility::use(UseContext use_context)
{
    //START: TODO: Move to different place - that's gonna be used a lot
    //Create rectangular area between ball origin and character origin
    Area3D *area3d = memnew(Area3D);
    CollisionShape3D *hitbox = memnew(CollisionShape3D);
    area3d->add_child(hitbox);
    BoxShape3D *hitboxShape = memnew(BoxShape3D);

    //Calculate length between character and ball
    //TODO: Get TundraBall

    Entity* caster = use_context.get_user();

    //Maybe buff/debuff under the hood?
    TundraBall* tundraBall;

    float hitboxWidth = 30.0f;
    float hitboxLength = use_context.get_user()->get_position().distance_to(tundraBall->get_position());

    hitboxShape->set_size(Vector3(hitboxWidth, 0, hitboxLength));

    hitbox->set_shape(hitboxShape);

    caster->add_child(area3d);

    hitbox->look_at(use_context.get_target_position());
    //END
    
    TypedArray<Area3D> colliders = area3d->get_overlapping_areas();

    for(int i = 0;i<colliders.size();i++)
    {
        //TODO: Figure out what can be used to retrieve variant as type
        //Area3D* collider =  Object::cast_to<Area3D>(&(*colliders[i]));
        Area3D* collider = Object::cast_to<Area3D>((Object*)colliders[i]);
        printf("Colliding Area3D: %s\n", String(collider->get_name()).ascii().get_data());

        //Here damage should be dealt to entity that owns collider
    }

    //Hitbox no longer needed - delete
    area3d->queue_free();
}

void TundraChainLashAbility::onTick()
{

}