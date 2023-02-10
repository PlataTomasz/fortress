#include "game_camera.hpp"
#include <classes/node3d.hpp>
#include <variant/vector3.hpp>

using namespace godot;

Vector3 GameCamera::CAMERA_OFFSET = Vector3(-1,0,-1);

GameCamera::GameCamera()
{
    followedNode = nullptr;
    freeCam = true;
    
    //TODO: Find alternative for callable_mp
    //connect("ready", callable_mp(this, &GameCamera::ready));
}

void GameCamera::ready()
{
    //TODO: Find alternative for callable_mp
    //get_tree()->connect("process_frame", callable_mp(this, &GameCamera::process));
    //That may help when I'll make manager responsible for camera
    //camera->connect("tree_exiting", callable_mp(this, &GameCamera::onCameraNodeExpire));
}

void GameCamera::onCameraNodeExpire()
{
    followedNode = nullptr;
    enableFreeCam();
}

void GameCamera::setFollowedNode(Node3D* node)
{
    followedNode = node;
}

void GameCamera::startFollowingNode(Node3D* node)
{
    followedNode = node;
    freeCam = false;
}

void GameCamera::enableFreeCam()
{
    freeCam = true;
}

void GameCamera::process()
{
    //Camera behaviour
    /*
        - Free cam
        - Tracking entity
    */

    if(!freeCam)
    {
        //TODO: Check if Followed node is still valid
        if(followedNode)
        {
            //printf("Followed node: %s\n", String(followedNode->get_name()).ascii().get_data());
            //TODO: Apply offset, so camera POV won't change upon 
            Vector3 camPos = this->get_position();
            Vector3 nodePos = followedNode->get_position();
            camPos.x = nodePos.x+GameCamera::CAMERA_OFFSET.x;
            camPos.z = nodePos.z+GameCamera::CAMERA_OFFSET.z;
            this->set_position(camPos);
        }
    }
}
