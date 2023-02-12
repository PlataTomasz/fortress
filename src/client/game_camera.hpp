#if !defined(GAME_CAMERA_HPP)
#define GAME_CAMERA_HPP

#include <classes/camera3d.hpp>
#include <variant/vector3.hpp>
#include <classes/node3d.hpp>

using namespace godot;

//Maybe changing it into camera controller would do better job?
class GameCamera : public Camera3D
{
GDCLASS(GameCamera, Camera3D);

protected:
static void _bind_methods(){};

protected:
    static Vector3 CAMERA_OFFSET;

    bool freeCam;

    Node3D *followedNode;

    /**
     * Changes currecntly followed node and disables freecam
    */
    void setFollowedNode(Node3D *node);
public:
    void _ready() override;
    void _exit_tree() override;
    void _process(double delta);

    void startFollowingNode(Node3D *node);
    void enableFreeCam();

    GameCamera();
    ~GameCamera(){};
};

#endif // GAME_CAMERA_HPP
