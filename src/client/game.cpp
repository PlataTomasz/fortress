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
#include "entities/mercenaries/mercenary.hpp"

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

    GameCamera *tmp_camera = (GameCamera*)get_node(NodePath("Camera"));
    if(tmp_camera)
    {
        this->camera = tmp_camera;
        std::cout<<"Game Camera detected!"<<std::endl;
    }
    else
    {
        //TODO: Load map from file - currently left in undefined state
        std::cout<<"Camera was not loaded!"<<std::endl;
    }

    Mercenary *ent = memnew(Mercenary);
    ent->set_name("ControlledEntity");
    this->add_child(ent);
    ent->set_position(Vector3( 2, 2, 2));
    
    Vector3 redSpawnPoint = Vector3();
    Node3D *redSpawnNode = (Node3D*)get_node(NodePath("Map/SpawnRed"));

    if(!redSpawnNode)
    {
        printf("No spawn node defined! Defaulting to map center (0, 0)");
    }
    else
    {
        redSpawnPoint = redSpawnNode->get_position();
    }

    player = new Player();
    player->controlledEntity = ent;
    player->controlledEntity->set_position(redSpawnPoint);

    camera->startFollowingNode(ent);
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
    //Casting to InputEventMouseButton - If succeeds: It is valid type
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
            Entity *ent = memnew(Entity);

            ent->set_position(worldPos);

            ent->set_name("DEBUG_BOI");
            add_child(ent);

            //TODO: Check if below works for different look_at Vector3 values
            ent->look_at(Vector3(0,0,0));
            Vector3 currRotation = ent->get_rotation();
            printf("Angles(rad): { %f, %f, %f}\n", currRotation.x, currRotation.y, currRotation.z);
            printf("Angles(deg): { %f, %f, %f}\n", currRotation.x*180/M_PI, (currRotation.y*180/M_PI), currRotation.z*180/M_PI);
            printf("Cosine of y angle: %f\n", cos(currRotation.y));
            printf("Sine of y angle: %f\n", sin(currRotation.y));
        }
        else if(event_ptr->is_action_pressed("movement"))
        {
            std::cout<<"MOVEMENT_ACTION"<<std::endl;
            player->controlledEntity->set_position(worldPos);
            //TODO: Send propper movement command - Check AStar Node
        }
    }
    else if(const InputEventKey *event_ptr = Object::cast_to<InputEventKey>(event.ptr()))
    {
        if(event_ptr->is_action_pressed("cast_ability_1"))
        {
            printf("Q press\n");
            player->controlledEntity->castAbility(1);
        }
        else if(event_ptr->is_action_pressed("cast_ability_2"))
        {
            printf("W press\n");
            player->controlledEntity->castAbility(2);
        }
        else if(event_ptr->is_action_pressed("cast_ability_3"))
        {
            printf("E press\n");
            player->controlledEntity->castAbility(3);
        }
        else if(event_ptr->is_action_pressed("cast_ability_4"))
        {
            printf("R press\n");
            player->controlledEntity->castAbility(4);
        }
    }
}

void Game::_bind_methods()
{   

}