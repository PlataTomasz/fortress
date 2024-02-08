#include <shared/abilities/aal/aal_straight_through_heart.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/box_shape_3d.h>
#include <shared/string_names/game_string_names.h>
#include <scene/resources/packed_scene.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>

AalStraightThroughHeart::AalStraightThroughHeart()
{
    //Preload content
    lightning_mesh = ResourceLoader::load("res://vfx/aal_stth.tscn");

    hit_area_width = 2.0;

    setup_hitboxes();
    setup_visuals();
}


//NOTE: That ability is prototype - should behave a bit differently
void AalStraightThroughHeart::use_impl(UseContext& use_context)
{
    ERR_FAIL_NULL(owner);

    owner->add_child(hit_area);

    TypedArray<Area3D> hit_areas = hit_area->get_overlapping_areas();
    for(int i = 0;i<hit_areas.size();i++)
    {
        Area3D* area = static_cast<Area3D*>(&*hit_areas[i]);
        
        Entity* parent = static_cast<Entity*>(area->get_parent());

        if(parent->is_in_group(GameStringNames::get_singleton()->ENTITIES_GROUP))
        {
            //FIXME: take_damage method no longer exists on Entity class - instead use DamageableComponent::take_damage.
            //TODO: Currently passes through all units
            /*
            parent->take_damage(memnew(DamageObject(
                DamageType::DAMAGE_MAGICAL,
                50,
                this->owner.get()
            )));
            */
        }
    }

    owner->remove_child(hit_area);

}

void AalStraightThroughHeart::ready_impl()
{
    
}

void AalStraightThroughHeart::setup_hitboxes()
{
    hit_area = memnew(Area3D);
    hit_area->set_name("AalStthHitbox");
    CollisionShape3D* hit_area_collision_shape = memnew(CollisionShape3D);
    BoxShape3D* shape = memnew(BoxShape3D);

    shape->set_size(Vector3(hit_area_width, 1, hit_area_length));
    hit_area_collision_shape->set_shape(shape);
    hit_area->add_child(hit_area_collision_shape);
    //Offset because center is origin - half length for rectangular hitbox
    hit_area->set_position(Vector3(0, 0, -(80+0.6)));
}

void AalStraightThroughHeart::setup_visuals()
{
    MeshInstance3D* lightning_mesh_instance = static_cast<MeshInstance3D*>((*lightning_mesh)->instantiate());
    lightning_mesh_instance->set_position(Vector3(0, 0, -(80+0.6)));
    Ref<PlaneMesh> mesh = lightning_mesh_instance->get_mesh();
    mesh->set_size(Size2(2, 160));

    owner->add_child(lightning_mesh_instance);
}