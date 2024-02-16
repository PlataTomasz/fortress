#if !defined(GAME_CAMERA_HPP)
#define GAME_CAMERA_HPP

#include <scene/3d/camera_3d.h>
#include <core/math/vector3.h>
#include <scene/3d/node_3d.h>



//Maybe changing it into camera controller would do better job?
class GameCamera : public Camera3D
{
GDCLASS(GameCamera, Camera3D);

protected:
static void _bind_methods(){};

protected:
    static Vector3 CAMERA_OFFSET;

    bool freeCam = false;

    Node3D *followedNode = nullptr;

    /**
     * Changes currecntly followed node and disables freecam
    */
    void setFollowedNode(Node3D *node);
public:
    void _ready();
    void _exit_tree();
    void process_frame();

    void startFollowingNode(Node3D *node);
    void enableFreeCam();

    GameCamera();
    ~GameCamera(){};
};

#endif // GAME_CAMERA_HPP
