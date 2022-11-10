#include "game.hpp"
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include "entities/entity.hpp"
#include <iostream>

Game::Game()
{

}

Game::~Game()
{
    
}

void Game::_ready()
{
    Node3D *tmp_mapInstance = get_node<Node3D>(NodePath("Map"));
    if(tmp_mapInstance)
    {
        this->mapInstance = tmp_mapInstance;
        std::cout<<"Map detected!"<<std::endl;
    }
    else
    {
        //TODO: Load map from file - currently left in undefined state
        std::cout<<"Map was not loaded!"<<std::endl;
    }

    Camera3D *tmp_camera = get_node<Camera3D>(NodePath("Camera"));
    if(tmp_camera)
    {
        this->camera = tmp_camera;
        std::cout<<"Camera detected!"<<std::endl;
    }
    else
    {
        //TODO: Load map from file - currently left in undefined state
        std::cout<<"Camera was not loaded!"<<std::endl;
    }
}

Vector3 Game::screenToWorld(const Vector2 &screenPos)
{
    
    //TODO: Project need to be used on camera node

    Vector3 roughWorldPos = camera->project_position(screenPos, 1000);
    Vector3 clickPos = camera->project_ray_origin(screenPos);

    double l = (roughWorldPos.x - clickPos.x);
    double m = (roughWorldPos.y - clickPos.y);
    double n = (roughWorldPos.z - clickPos.z);

    double world_x = clickPos.x - (clickPos.y/m)*l;
    double world_z = clickPos.z - (clickPos.y/m)*n;

    //y is zero because that doesn't matter
    return Vector3(world_x, 0, world_z);
}

void Game::_unhandled_input(const Ref<InputEvent> &event)
{
    const InputEventMouseButton *event_ptr = Object::cast_to<InputEventMouseButton>(event.ptr());
    //Check if we got MouseButton input event
    if(event_ptr)
    {
        Vector2 screenPos = event_ptr->get_position();
        Vector3 worldPos = screenToWorld(screenPos);

        //Convert screen to world cordinates
        printf("{ %f, %f, %f}\n", worldPos.x, worldPos.y, worldPos.z);

        //Create entity
        MeshInstance3D *meshInstance = memnew(MeshInstance3D);

        BoxMesh *boxMesh = memnew(BoxMesh);

        Ref<Mesh> mesh(boxMesh);
        boxMesh->set_size(Vector3(0.1,0.1,0.1));


        meshInstance->set_mesh(mesh);

        Entity *ent = memnew(Entity);

        ent->add_child(meshInstance);

        ent->set_position(worldPos);

        ent->set_name("DEBUG_BOI");
        add_child(ent);

        ent->look_at(Vector3(0,0,0));
        Vector3 currRotation = ent->get_rotation();
        printf("Angles(rad): { %f, %f, %f}\n", currRotation.x, currRotation.y, currRotation.z);
        printf("Angles(deg): { %f, %f, %f}\n", currRotation.x*180/M_PI, (currRotation.y*180/M_PI), currRotation.z*180/M_PI);
        printf("Cosine of y angle: %f\n", cos(currRotation.y));
        printf("Sine of y angle: %f\n", sin(currRotation.y));

        //Make it move in the direction of worldPos(click world position)
        //meshInstance


        if(event_ptr->is_action_pressed("basic_attack"))
        {
            std::cout<<"ATTACK_ACTION"<<std::endl;

            //Player tries to use basic attack

            Node3D *entitiesNode = this->mapInstance->get_node<Node3D>(NodePath("Entities"));
            //Create new entity

            /*
            var raycast_origin = cam.project_ray_origin(event.position)
            var world_hitpos = raycast_origin + cam.project_ray_normal(event.position) * 1000
            */
        }
        else if(event_ptr->is_action_pressed("movement"))
        {
            std::cout<<"MOVEMENT_ACTION"<<std::endl;
        }
    }
}

void Game::_bind_methods()
{   

}