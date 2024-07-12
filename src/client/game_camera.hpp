#if !defined(GAME_CAMERA_HPP)
#define GAME_CAMERA_HPP

#include <scene/3d/camera_3d.h>
#include <core/math/vector3.h>
#include <scene/3d/node_3d.h>

class Mercenary;

//Maybe changing it into camera controller would do better job?
class GameCamera : public Camera3D
{
GDCLASS(GameCamera, Camera3D);

protected:
static void _bind_methods(){};
private:
    bool _camera_drag = false;
    bool _freecam_chase = false;

    void _init();
    void _process_frame();

    void _on_tracked_node_exiting();
    void _on_controlled_mercenary_changed(Mercenary *new_ent);
protected:
    static Vector3 CAMERA_OFFSET;
    static Vector3 CAMERA_SPEED_VECTOR;

    bool freecam = true;

    Node3D *tracked_node = nullptr;

    virtual void input(const Ref<InputEvent> &p_event) override;
    void _notification(int p_notification);
public:
    Vector3 screen_to_world(const Vector2& screen_pos);

    /**
     * Changes currecntly followed node and disables freecam
    */
    void set_tracked_node(Node3D *node);
    Node3D *get_tracked_node();

    void _ready();
    void _exit_tree();

    void startFollowingNode(Node3D *node);
    bool is_freecam();
    void set_freecam(bool p_freecam);

    GameCamera();
    ~GameCamera(){};
};

#endif // GAME_CAMERA_HPP
