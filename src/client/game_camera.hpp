#if !defined(GAME_CAMERA_HPP)
#define GAME_CAMERA_HPP

#include <scene/3d/camera_3d.h>

class GameCamera : public Camera3D
{
GDCLASS(GameCamera, Camera3D);

protected:
static void _bind_methods(){};

protected:
    bool freeCam;

    Node3D *followedNode;

    void ready();
    void setFollowedNode(Node3D *node);
    /**
     * Changes currecntly followed node and disables freecam
    */
    void process();
public:
    void startFollowingNode(Node3D *node);

    GameCamera();
    ~GameCamera(){};
};

#endif // GAME_CAMERA_HPP
