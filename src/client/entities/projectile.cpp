#include "projectile.hpp"
#include <godot_cpp/core/class_db.hpp>

Projectile::Projectile()
{

}

Projectile::~Projectile()
{
    
}

void Projectile::_ready()
{

    //connect("area_entered", this, "onCollision");
}

void Projectile::_bind_methods()
{

}
/*
void Projectile::onCollision(const Area3D &collider)
{
    //ClassDB::bind_method(D_METHOD("onCollision"), &Projectile::onCollision);
}
*/