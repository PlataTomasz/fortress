#include "game.hpp"
#include <scene/3d/node_3d.h>
#include <scene/3d/camera_3d.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>
#include <core/input/input_event.h>
#include <core/object/class_db.h>
#include <core/object/method_bind.h>
#include <core/core_bind.h>
#include <iostream>
#include "entities/entity.hpp"

Game::Game()
{
    //Register signals
    if(!Engine::get_singleton()->is_editor_hint())
    {
        connect("ready", callable_mp(this, &Game::_ready));
        //Allow node to process inputs
        set_process_unhandled_input(true);
        printf("%d\n", is_processing_unhandled_input());
    }
}

Game::~Game()
{
    
}

void Game::_ready()
{
    Node3D *tmp_mapInstance = (Node3D*)get_node(NodePath("Map"));
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

    Camera3D *tmp_camera = (Camera3D*)get_node(NodePath("Camera"));
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

void Game::unhandled_input(const Ref<InputEvent> &event)
{
    const InputEventMouseButton *event_ptr = Object::cast_to<InputEventMouseButton>(event.ptr());
    //Check if we got MouseButton input event
    if(event_ptr)
    {
        Vector2 screenPos = event_ptr->get_position();
        Vector3 worldPos = screenToWorld(screenPos);

        //Convert screen to world cordinates
        printf("{ %f, %f, %f}\n", worldPos.x, worldPos.y, worldPos.z);

        if(event_ptr->is_action_pressed("basic_attack"))
        {
            std::cout<<"ATTACK_ACTION"<<std::endl;

            //Player tries to use basic attack

            Node3D *entitiesNode = (Node3D*)(this->mapInstance->get_node(NodePath("Entities")));
            //Create new entity

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