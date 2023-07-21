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
#include <client/string_names/game_string_names.h>
#include <client/game_logic/abilities/ability.hpp>

Entity::Entity()
{
    DISABLE_IN_EDITOR();
    //TODO: Call virtual initialize(); ?
    connect("ready", callable_mp(this, &Entity::ready));
    connect("ready", callable_mp(this, &Entity::_shared_ready));

    SceneTree::get_singleton()->connect("physics_frame", callable_mp(this, &Entity::physics_frame));

    stats.health.get_max_health_stat().set_initial_value(1000);
    stats.health.set_current_value(1000);

    stats.physicalResistance.get_base().set_initial_value(100);
    stats.magicResistance.get_base().set_initial_value(100);

    //FIXME: Currently explicit recalculate call is required.
    stats.physicalResistance.recalculate();
    stats.magicResistance.recalculate();

    add_to_group(GameStringNames::get_singleton()->ENTITIES_GROUP);
}

Entity::~Entity()
{

}

void Entity::_bind_methods()
{
    //Health changed
    //ADD_SIGNAL(MethodInfo("health_change", PropertyInfo(Variant::FLOAT, "value")));
    ADD_SIGNAL(MethodInfo(GameStringNames::get_singleton()->ON_HEALTH_CHANGE, PropertyInfo(Variant::FLOAT, "new_health"), PropertyInfo(Variant::FLOAT, "old_health")));
    //Entity will die soon
    ADD_SIGNAL(MethodInfo(GameStringNames::get_singleton()->PRE_DEATH, PropertyInfo(Variant::OBJECT, "death_cause")));
    //Entity died
    ADD_SIGNAL(MethodInfo(GameStringNames::get_singleton()->ON_DEATH, PropertyInfo(Variant::OBJECT, "death_cause")));

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

Area3D* Entity::get_hitbox()
{
    return hitbox;
}

void Entity::physics_frame()
{
    //StatusEffect handling
    for(auto effect : applied_status_effects)
    {
        effect.value->on_process_frame_impl();
    }
}

bool Entity::remove_status_effect(String status_effect_name)
{
    return StatusEffectManager::get_singleton()->remove_status_effect(status_effect_name, this);
}

bool Entity::remove_status_effect(StatusEffect* status_effect)
{
    return StatusEffectManager::get_singleton()->remove_status_effect(status_effect, this);
}

StatusEffect *Entity::apply_status_effect(String status_effect_name, float duration, Entity *inflictor)
{
    return StatusEffectManager::get_singleton()->apply_status_effect(status_effect_name, duration, this, inflictor);
}


bool Entity::has_status_effect(String status_effect_name)
{
    if(get_status_effect(status_effect_name) != nullptr)
        return true;
    else
        return false;
}

StatusEffect *Entity::get_status_effect(String status_effect_name)
{
    for(auto effect : applied_status_effects)
    {
        if(effect.value->name == status_effect_name)
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

bool Entity::is_alive()
{
    return alive;
}

void Entity::kill(Entity* killer)
{
    //"killer" is what entity caused this entity to die

    emit_signal("pre_death");
    //At this point, entity is no longer considered alive
    alive = false;
    emit_signal("post_death");
}

void Entity::take_damage(DamageObject damage_object)
{
    /*
    //Entity is dead, damage won't apply
    if(!is_alive())
        return;
        */

    double final_damage;

    double current_health = stats.health.get_current_value();

    switch(damage_object.type)
    {
        case DAMAGE_PHYSICAL:
        {
            final_damage = damage_object.value * 100/(stats.physicalResistance+100);
        }
        break;

        case DAMAGE_MAGICAL:
        {
            final_damage = damage_object.value * 100/(stats.magicResistance+100);
        }
        break;

        default:
        {
            final_damage = damage_object.value;
        }
    }

    current_health -= final_damage;

    stats.health.set_current_value(current_health);

    emit_signal("health_change");

    if(current_health <= 0)
    {
        kill(damage_object.inflictor);
    }
}
//TODO: Replace with ObjectPtr
void Entity::add_child_notify(Node* node)
{
    if(dynamic_cast<Ability*>(node))
    {
    
    }
    else
    {

    }
}



AbilityChargeData::Error Entity::start_charging_ability(IChargeable* ability)
{
    

    return AbilityChargeData::Error::OK;
}

/*
Entity* Entity::create_empty()
{
    Entity* ent = new Entity();
    ent->set_name("NONE");

    return ent;
}
*/