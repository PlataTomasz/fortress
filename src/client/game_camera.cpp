#include "game_camera.hpp"
#include <scene/3d/node_3d.h>
#include <core/math/vector3.h>
#include <shared/helper_macros.h>

Vector3 GameCamera::CAMERA_OFFSET = Vector3(0, 2, 3.5);

GameCamera::GameCamera()
{
    DISABLE_IN_EDITOR();
    followedNode = nullptr;
    freeCam = true;
    set_rotation_degrees(Vector3(-45,0,0));
    set_position(Vector3(0, 10, 5));

    SceneTree::get_singleton()->connect("process_frame", callable_mp(this, &GameCamera::process_frame));
}

void GameCamera::_ready()
{
}

void GameCamera::_exit_tree()
{
    DISABLE_IN_EDITOR();
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

void GameCamera::process_frame()
{
    DISABLE_IN_EDITOR();

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
            /*
            camPos.x = nodePos.x+GameCamera::CAMERA_OFFSET.x;
            camPos.x = nodePos.y+GameCamera::CAMERA_OFFSET.y;
            camPos.z = nodePos.z+GameCamera::CAMERA_OFFSET.z;
            */
            this->set_position(camPos);
        }
    }
}
