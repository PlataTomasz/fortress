#include "entity.hpp"
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/class_db.hpp>

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::_ready()
{
    Area3D *area3d = memnew(Area3D);
    add_child(area3d);
    area3d->connect("area_entered", Callable(this, "onCollision"));
}

void Entity::onCollision(Area3D *collider)
{
    //Area3D *collider = Object::cast_to<Area3D>(area3d);

    if(collider)
    {
        printf("Collision with: %s", collider->get_name());
        this->queue_free();
    }
    else
        printf("Invalid collider!\n");
}

void Entity::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("onCollision", "collider"), &Entity::onCollision);
}

//
void Entity::movementProcess()
{
    //FIXME: Assuming that game logic tickrate(aka physics tickrate) is 60 per second
    float movementSpeedPerTick = this->movementSpeed/60.0f;

    Vector3 currPos = get_position();
    auto rotation = get_rotation();

    auto angleRad = rotation.y; //Alpha angle
    auto invertedAngleRad = M_PI - rotation.y; //Beta angle

    /*
    // This block causes entities to simulate circular movement

    auto newX = cos(invertedAngleRad)*movementSpeedPerTick;
    auto newY = sin(invertedAngleRad)*movementSpeedPerTick;
    */

    auto newX = cosf(angleRad)*movementSpeedPerTick;
    auto newZ = sinf(angleRad)*movementSpeedPerTick;

    float nextPos_x = currPos.x - newZ;
    float nextPos_z = currPos.z - newX;

    set_position(Vector3(nextPos_x, currPos.y, nextPos_z));
}

void Entity::_physics_process(double delta)
{
    movementProcess();
    currLifetime++;

    if(currLifetime >= maxLifetime)
    {
        this->queue_free();
    }
}