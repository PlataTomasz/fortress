#include <shared/abilities/aal/aal_strucked_twice.h>
#include <scene/3d/collision_shape_3d.h>
#include <scene/resources/sphere_shape_3d.h>

#include <scene/3d/area_3d.h>

void AalStruckedTwice::use_impl(UseContext& use_context)
{
    const double radius_sq = 15*15;

    //Calls down lightning to hit every position in radius around it
    List<Node*> nodes;
    SceneTree::get_singleton()->get_nodes_in_group("aal_struck_twice_markers", &nodes);
    Vector3 user_position = use_context.get_user()->get_global_position();

    for(Node* element : nodes)
    {
        Node3D* position_marker = static_cast<Node3D*>(element);
        Vector3 marker_position = position_marker->get_global_position();

        double x = user_position.x;
        double y = user_position.z;
        double h = marker_position.x;
        double k = marker_position.z;

        bool is_point_in_radius = ( (x-h)*(x-h)+(y-k)*(y-k) <= radius_sq);

        if(is_point_in_radius)
        {
            //hit_area->set_global_position(marker_position);
            Area3D* hit_area = (Area3D*)position_marker->get_node(NodePath("HitArea"));

            print_line(hit_area->get_class_name());
            hit_area->get_overlapping_areas();
            TypedArray<Area3D> areas = hit_area->get_overlapping_areas();

            for(int i = 0;i<areas.size();i++)
            {
                Area3D* area = (Area3D*)&*(areas[i]);
                print_line("Current area: ", area);

                Entity* parent = static_cast<Entity*>(area->get_parent());
                //if(parent->get_parent() && parent->get_parent()->get_name() == "Entities")
                // Check if node is entity
                if(parent != use_context.get_user())
                {
                    //TODO: Take damage is is DamageableComponent
                }
            }
        }
        else
        {
            print_line("Point is NOT in radius! Failed!: ", position_marker);
        }

    }
}

//Called whenever any entity is hit with ability, that was casted by owner
void AalStruckedTwice::on_ability_hit(const AbilityHitData& hit_data)
{
    //TODO: Remove position_marker after "expire_time" seconds
    //TODO: Shouldn't count hits if that ability was on cooldown
    Node3D* position_marker = memnew(Node3D);
    position_marker->set_global_position(hit_data.hit_position);
    position_marker->add_to_group("aal_struck_twice_markers");

    Area3D* hit_area = memnew(Area3D);
    hit_area->set_name("HitArea");
    CollisionShape3D* hit_area_shape_node = memnew(CollisionShape3D);
    hit_area_shape_node->set_name("HitShape");
    SphereShape3D* hit_area_shape = memnew(SphereShape3D);
    hit_area_shape_node->set_shape(hit_area_shape);
    hit_area->add_child(hit_area_shape_node);

    hit_area_shape->set_radius(1);
    hit_area->add_child(hit_area_shape_node);
    position_marker->add_child(hit_area);
}

void AalStruckedTwice::ready_impl()
{
    //Setting up collisions
    effect_area = memnew(Area3D);
    CollisionShape3D* effect_area_shape_node = memnew(CollisionShape3D);
    SphereShape3D* effect_area_shape = memnew(SphereShape3D);
    effect_area_shape->set_radius(15);
    effect_area_shape_node->set_shape(effect_area_shape);
    effect_area->add_child(effect_area_shape_node);

    get_owner()->add_child(effect_area);
}

AalStruckedTwice::AalStruckedTwice()
{

}