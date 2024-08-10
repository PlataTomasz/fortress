#include "projectile_entity.h"

void ProjectileEntity::_tickv() {
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

void ProjectileEntity::set_target(Entity *new_target) {
    target = new_target;
}

Entity *ProjectileEntity::get_target() {
    return target;
}


void ProjectileEntity::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_target"), &ProjectileEntity::get_target);
    ::ClassDB::bind_method(D_METHOD("set_target"), &ProjectileEntity::set_target);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_NODE_TYPE, Entity::get_class_static()), "set_target", "get_target");
}