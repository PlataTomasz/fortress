#include "game_camera.hpp"

GameCamera::GameCamera()
{
    followedNode = nullptr;
    freeCam = true;
    connect("ready", callable_mp(this, &GameCamera::ready));
}

void GameCamera::ready()
{
    get_tree()->connect("process_frame", callable_mp(this, &GameCamera::process));
}

void GameCamera::setFollowedNode(Node3D *node)
{
    followedNode = node;
}

void GameCamera::startFollowingNode(Node3D *node)
{
    followedNode = node;
    freeCam = false;
}

void GameCamera::process()
{
    //Camera behaviour
    /*
        - Free cam
        - Tracking entity
    */

    if(freeCam)
    {
        printf("Freecam\n");
    }
    else
    {
        //TODO: Check if Followed node is still valid
        printf("Locked camera\n");

        if(followedNode)
        {
            printf("Followed node: %s", followedNode->get_name());
            //TODO: Apply offset, so camera POV won't change upon 
            Vector3 camPos = this->get_position();
            Vector3 nodePos = followedNode->get_position();
            camPos.x = nodePos.x;
            camPos.z = nodePos.z;
            this->set_position(camPos);
        }
        else
        {
            //What should happen if Followed node is no longer valid?
            printf("Followed node was never set!");
        }
    }
}
