#include "projectile_entity.h"

#include <scene/3d/physics/area_3d.h>

#include <shared/entities/components/damage/damageable_component.h>

void ProjectileEntity::_tickv() {
    if(!target) return;

    DamageableComponent *damageable = target->get_damageable_component();
    if(damageable && damageable->is_dead()) {
        // Invalidate projectiles aimed at already dead entities
        queue_free();
    }

    // It definitely goes somewhere, but I'm not sure If it stops in the right place
    float delta = SceneTree::get_singleton()->get_physics_process_time();

    float movement_speed = 2.0;

	float movement_delta = movement_speed * delta;
    Vector3 direction_to_target = (this->get_position()).direction_to(target->get_position());
	Vector3 velocity = direction_to_target * Vector3(movement_delta, movement_delta, movement_delta);

	Vector3 new_position = this->get_position() + velocity;

	this->set_position(new_position);
	this->look_at(target->get_position(), Vector3(0, 1, 0), true);
}

void ProjectileEntity::_readyv() {
    ERR_FAIL_NULL(hitbox);
    hitbox->connect("area_entered", callable_mp(this, &ProjectileEntity::_on_hit_detect));
}

void ProjectileEntity::_on_hit_detect(Area3D *detected_area) {
    if(detected_area->is_in_group("hurtbox")) {
        if(Entity *ent = Object::cast_to<Entity>(detected_area->get_parent())) {
            _on_hit_entity(ent);
        }
    }
}

void ProjectileEntity::_on_hit_entity(Entity *hit_entity) {
    ERR_FAIL_NULL(hit_entity);
    if(hit_entity == target) {
        if(DamageableComponent *damageable = hit_entity->get_damageable_component()) {
            //damageable->take_damage(memnew(DamageObject(DamageObject::DAMAGE_PHYSICAL, DamageObject::BASIC_ATTACK_DAMAGE, 15, creator)));
            damageable->take_damage(memnew(DamageObject(DamageObject::DAMAGE_PHYSICAL, DamageObject::BASIC_ATTACK_DAMAGE, 15, creator)));
        }
        queue_free();
    }
}

void ProjectileEntity::set_target(Entity *new_target) {
    target = new_target;
}

Entity *ProjectileEntity::get_target() {
    return target;
}

void ProjectileEntity::set_hitbox(Area3D *new_hitbox) {
    hitbox = new_hitbox;
}

Area3D *ProjectileEntity::get_hitbox() {
    return hitbox;
}

void ProjectileEntity::set_creator(Entity *new_creator) {
    creator = new_creator;
}

Entity *ProjectileEntity::get_creator() {
    return creator;
}

void ProjectileEntity::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_target"), &ProjectileEntity::get_target);
    ::ClassDB::bind_method(D_METHOD("set_target"), &ProjectileEntity::set_target);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_NODE_TYPE, Entity::get_class_static()), "set_target", "get_target");

    ::ClassDB::bind_method(D_METHOD("get_hitbox"), &ProjectileEntity::get_hitbox);
    ::ClassDB::bind_method(D_METHOD("set_hitbox"), &ProjectileEntity::set_hitbox);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hitbox", PROPERTY_HINT_NODE_TYPE, Area3D::get_class_static()), "set_hitbox", "get_hitbox");
}