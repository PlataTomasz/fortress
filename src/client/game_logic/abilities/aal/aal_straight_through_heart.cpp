#include <client/game_logic/abilities/aal/aal_straight_through_heart.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/box_shape_3d.h>
#include <client/string_names/game_string_names.h>
#include <scene/resources/packed_scene.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>

AalStraightThroughHeart::AalStraightThroughHeart()
{
    //Preload content
    lightning_mesh = ResourceLoader::load("res://vfx/aal_stth.tscn");

    double hit_area_width = 2.0;

    hit_area = memnew(Area3D);

    //TODO: Offset position of that hitbox
    hit_area->set_name("HitArea");
    CollisionShape3D* hit_area_shape_node = memnew(CollisionShape3D);
    hit_area_shape_node->set_name("HitShape");

    BoxShape3D* hit_area_shape = memnew(BoxShape3D);
    //That ability should have global range
    hit_area_shape->set_size(Vector3(hit_area_width, 1, 160));
    hit_area_shape_node->set_shape(hit_area_shape);
    hit_area->add_child(hit_area_shape_node);
}


//NOTE: That ability is prototype - should behave a bit differently
void AalStraightThroughHeart::use_impl(UseContext use_context)
{
    
    hit_area->set_position(Vector3(0, 0, -(80+0.6)));

    owner->add_child(hit_area);

    MeshInstance3D* lightning_mesh_instance = static_cast<MeshInstance3D*>((*lightning_mesh)->instantiate());
    lightning_mesh_instance->set_position(Vector3(0, 0, -(80+0.6)));
    Ref<PlaneMesh> mesh = lightning_mesh_instance->get_mesh();
    mesh->set_size(Size2(2, 160));

    owner->add_child(lightning_mesh_instance);


    TypedArray<Area3D> hit_areas = hit_area->get_overlapping_areas();
    for(int i = 0;i<hit_areas.size();i++)
    {
        Area3D* area = static_cast<Area3D*>(&*hit_areas[i]);
        
        Entity* parent = static_cast<Entity*>(area->get_parent());

        if(parent->is_in_group(GameStringNames::get_singleton()->ENTITIES_GROUP))
        {
            //TODO: Currently passes through all units
            parent->take_damage({
                DamageType::DAMAGE_MAGICAL,
                50,
                this->owner
            });
        }
    }

    owner->remove_child(hit_area);

}